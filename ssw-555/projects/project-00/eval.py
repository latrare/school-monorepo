import datetime
from collections import namedtuple

import lark


MONTH_MAP = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP',
             'OCT', 'NOV', 'DEC']


class Individual(object):
    def __init__(self, id_):
        self.id_ = id_
        self.deathdate = None

    def set_name(self, first, last):
        self.name = {'first': first.capitalize(), 'last': last.capitalize()}

    def set_birth(self, date):
        if not date:
            raise ValueError('Individual {} has no birthdate.'.format(self.id_))
        self.birthdate = date
        self._check_dates()

    def set_death(self, date):
        self.deathdate = date
        self._check_dates()

    def set_sex(self, sex):
        self.sex = sex

    def _check_dates(self):
        if self.birthdate and self.deathdate:
            if self.birthdate > self.deathdate:
                    raise ValueError(
                        'Individual {} has a death before they were born.'
                        .format(self.id_))

    def __repr__(self):
        return ('Individual({}, {}, {})'
                .format(self.id_, self.name['first'] + ' ' + self.name['last'],
                        self.sex))


class Family(object):
    def __init__(self, id_):
        self.id_ = id_


IndividualId = namedtuple('IndividualId', ['id_'])
FamilyId = namedtuple('FamilyId', ['id_'])

NameExpr = namedtuple('NameExpr', ['first', 'last'])
BirthExpr = namedtuple('BirthExpr', 'date')
DateExpr = namedtuple('DateExpr', ['year', 'month', 'day'])
DeathExpr = namedtuple('DeathExpr', 'date')
SexExpr = namedtuple('SexExpr', 'sex')

ChildExpr = namedtuple('ChildExpr', 'family_ref')
SpouseExpr = namedtuple('SpouseExpr', 'family_ref')
FamilyRef = namedtuple('FamilyRef', 'family_id')
IndividualRef = namedtuple('IndividualRef', 'individual_id')


def find_arg(arg_list, type_):
    arg = [a for a in arg_list if isinstance(a, type_)]
    if arg:
        return arg[0]
    else:
        return None


class GedcomTransformer(lark.Transformer):
    def birt_stmt(self, ts):
        (_, date) = ts
        return BirthExpr(date)

    def deat_stmt(self, ts):
        (_, date) = ts
        return DeathExpr(date)

    def date_stmt(self, ts):
        (_, t_day, t_month, t_year) = ts
        return datetime.date(year=int(t_year.value),
                             month=MONTH_MAP.index(t_month.value) + 1,
                             day=int(t_day.value))

    def famc_stmt(self, ts):
        (_, t_fid) = ts
        return ChildExpr(FamilyRef(int(t_fid.value)))

    def fams_stmt(self, ts):
        (_, t_fid) = ts
        return SpouseExpr(FamilyRef(int(t_fid.value)))

    def name_stmt(self, ts):
        (_, t_first, t_last) = ts
        return NameExpr(t_first.value, t_last.value)

    def sex_stmt(self, ts):
        (_, t_sex) = ts
        return SexExpr(t_sex.value)

    def note_stmt(self, ts):
        # Ignore notes
        pass

    def indi_stmt(self, *ts):
        (inner_list,) = ts
        indi_id = inner_list[1]
        # Arguments can be in any order, so find them by type
        return (IndividualId(int(indi_id)), (tuple(inner_list[2:]),))

    def marr_stmt(self, ts):
        pass

    def husb_stmt(self, ts):
        pass

    def wife_stmt(self, ts):
        pass

    def chil_stmt(self, ts):
        pass

    def fam_stmt(self, *ts):
        (inner_list,) = ts
        fam_id = inner_list[1]
        print(inner_list[1:])
        return (FamilyId(int(fam_id)), (None,))


def main():
    with open('family.gedcom') as f:
        parser = lark.Lark.open('gedcom.lark')
        # Parse the given gedcom file based on the gedcom.lark grammar
        tree = parser.parse(f.read())
        lark.tree.pydot__tree_to_png(tree, 'family-parsed.png')
        # Build the AST
        ast = GedcomTransformer().transform(tree)
        print(ast.pretty())
        print(ast)
        # Evaluate
        # Output family tree
        lark.tree.pydot__tree_to_png(ast, 'family-eval.png')


if __name__ == '__main__':
    main()
