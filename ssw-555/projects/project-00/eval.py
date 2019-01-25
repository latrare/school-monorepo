import datetime
from collections import namedtuple

import lark


MONTH_MAP = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP',
             'OCT', 'NOV', 'DEC']


Individual = namedtuple('Individual', ['id_', 'name', 'birth', 'death', 'sex'])
Family = namedtuple('Family', ['id_',])

Name = namedtuple('Name', ['first', 'last'])
Birth = namedtuple('Birth', 'date')
Date = namedtuple('Date', ['year', 'month', 'day'])
Death = namedtuple('Death', 'date')
Sex = namedtuple('Sex', 'sex')

Child = namedtuple('Child', 'family_ref')
Spouse = namedtuple('Spouse', 'family_ref')
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
        return Birth(date)

    def deat_stmt(self, ts):
        (_, date) = ts
        return Death(date)

    def date_stmt(self, ts):
        (_, t_day, t_month, t_year) = ts
        return Date(t_year.value, t_month.value, t_year.value)

    def famc_stmt(self, ts):
        (_, t_fid) = ts
        return Child(FamilyRef(t_fid.value))

    def fams_stmt(self, ts):
        (_, t_fid) = ts
        return Spouse(FamilyRef(t_fid.value))

    def name_stmt(self, ts):
        (_, t_first, t_last) = ts
        return Name(t_first.value, t_last.value)

    def sex_stmt(self, ts):
        (_, t_sex) = ts
        return Sex(t_sex.value)

    def note_stmt(self, ts):
        # Ignore notes
        pass

    def indi_stmt(self, *ts):
        (inner_list,) = ts
        indi_id = inner_list[1]
        # Arguments can be in any order, so find them by type
        name = find_arg(inner_list, Name)
        birth = find_arg(inner_list, Birth)
        death = find_arg(inner_list, Death)
        sex = find_arg(inner_list, Sex)
        # Assemble individual
        return Individual(indi_id.value, name, birth, death, sex)


def main():
    with open('example.gedcom') as f:
        parser = lark.Lark.open('gedcom.lark')
        # Parse the given gedcom file based on the gedcom.lark grammar
        tree = parser.parse(f.read())
        # Build the AST
        ast = GedcomTransformer().transform(tree)
        print(ast.pretty())
        # Evaluate
        # Output family tree


if __name__ == '__main__':
    main()
