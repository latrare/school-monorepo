from collections import namedtuple


BirthExpr = namedtuple('Birth', ('date',))
DeathExpr = namedtuple('Death', ('date',))
FamcExpr = namedtuple('Famc', ('ref',))
FamsExpr = namedtuple('Fams', ('ref',))
NameExpr = namedtuple('Name', ('first', 'last'))
SexExpr = namedtuple('Sex', ('sex', ))
FamilyRef = namedtuple('FamilyRef', ('ref',))
IndividualRef = namedtuple('IndividualRef', ('ref',))
ChildExpr = namedtuple('Child', ('ref',))
MarriageExpr = namedtuple('Marriage', ('date',))
DivorceExpr = namedtuple('Divorce', ('date',))
HusbandExpr = namedtuple('Husband', ('ref',))
WifeExpr = namedtuple('Wife', ('ref',))
