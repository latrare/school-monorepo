import datetime

import lark

from expressions import *
from models import Family, Individual


_MONTH_MAP = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 'JUL', 'AUG', 'SEP',
             'OCT', 'NOV', 'DEC']


class GedcomTransformer(lark.Transformer):
    individuals = {}
    families = {}

    def indi_stmt(self, *ts):
        (args,) = ts
        individual = Individual.from_args(args)
        self.individuals[individual.id_] = individual
        return individual

    def fam_stmt(self, *ts):
        (args,) = ts
        family = Family.from_args(args)
        self.families[family.id_] = family
        return family

    def birt_stmt(self, ts):
        (_, date) = ts
        return BirthExpr(date)

    def deat_stmt(self, ts):
        (_, date) = ts
        return DeathExpr(date)

    def date_stmt(self, ts):
        (_, t_day, t_month, t_year) = ts
        return datetime.date(year=int(t_year.value),
                             month=_MONTH_MAP.index(t_month.value) + 1,
                             day=int(t_day.value))

    def famc_stmt(self, ts):
        (_, fid) = ts
        return FamcExpr(fid.value)

    def fams_stmt(self, ts):
        (_, fid) = ts
        return FamsExpr(fid.value)

    def name_stmt(self, ts):
        (_, first, last) = ts
        return NameExpr(first.value, last.value)

    def sex_stmt(self, ts):
        (_, sex) = ts
        return SexExpr(sex.value)

    def marr_stmt(self, ts):
        (_, date) = ts
        return MarriageExpr(date)

    def husb_stmt(self, ts):
        (_, id_) = ts
        return HusbandExpr(IndividualRef(id_.value))

    def wife_stmt(self, ts):
        (_, id_) = ts
        return WifeExpr(IndividualRef(id_.value))

    def div_stmt(self, ts):
        (_, date) = ts
        return DivorceExpr(date)

    def chil_stmt(self, ts):
        (_, id_) = ts
        return ChildExpr(IndividualRef(id_.value))

    def note_stmt(self, ts):
        # Ignore notes
        pass
