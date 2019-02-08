from expressions import *


def find_arg(arg_list, kind):
    arg = [a for a in arg_list if isinstance(a, kind)]
    if len(arg) == 1:
        return arg[0]
    if len(arg) > 1:
        return arg
    else:
        return []


class Family(object):
    @classmethod
    def from_args(cls, args):
        """Construct Family object from Transformer expressions."""
        family = cls()
        family.id_ = args[1].value
        marriages = find_arg(args, MarriageExpr)
        family.marriages = (marriages
                            if isinstance(marriages, list)
                            else [marriages,])
        family.marriages = [d.date for d in family.marriages]
        divorces = find_arg(args, DivorceExpr)
        family.divorces = (divorces
                            if isinstance(divorces, list)
                            else [divorces,])
        family.divorces = [d.date for d in family.divorces]
        husband = find_arg(args, HusbandExpr)
        if husband:
            family.husband = husband.ref
        wife = find_arg(args, WifeExpr)
        if wife:
            family.wife = wife.ref
        children = find_arg(args, ChildExpr)
        family.children = (children
                           if isinstance(children, list)
                           else [children,])
        family.children = [c.ref for c in family.children]
        return family


class Individual(object):
    @classmethod
    def from_args(cls, args):
        """Construct Individual object from Transformer expressions."""
        individual = cls()
        individual.id_ = args[1].value
        individual.birth = find_arg(args, BirthExpr).date
        death = find_arg(args, DeathExpr)
        individual.death = None if not death else death.date
        name = find_arg(args, NameExpr)
        individual.first_name = name.first
        individual.last_name = name.last
        individual.sex = find_arg(args, SexExpr).sex
        child_to = find_arg(args, FamcExpr)
        individual.child_to = (child_to
                               if isinstance(child_to, list)
                               else [child_to,])
        individual.child_to = [c.ref for c in individual.child_to]
        spouse_to = find_arg(args, FamsExpr)
        individual.spouse_to = (spouse_to
                                if isinstance(spouse_to, list)
                                else [spouse_to,])
        individual.spouse_to = [s.ref for s in individual.spouse_to]
        return individual
