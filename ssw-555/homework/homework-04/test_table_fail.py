import lark
from prettytable import PrettyTable
from nose.tools import assert_equals

from gedcom.models import Family, Individual
from gedcom.table import *
from gedcom.transformer import GedcomTransformer


def test_table_fail_empty():
    parsetree = (lark.Lark.open('gedcom/gedcom.lark', parser='earley')
                 .parse(""))
    tree = GedcomTransformer().transform(parsetree)
    families = {m.id: m for m in tree.children if isinstance(m, Family)}
    individuals = {m.id: m for m in tree.children
                   if isinstance(m, Individual)}

    # Create tables from parsing the TEST_GEDCOM
    family_table = create_family_table(families, individuals)
    individual_table = create_individual_table(individuals)

    # Create a table manually and get the string of it
    manual_family_table = PrettyTable()
    manual_family_table.field_names = [
        'ID',
        'Married',
        'Divorced',
        'Husband ID',
        'Husband Name',
        'Wife ID',
        'Wife Name',
        'Children',
    ]

    manual_individual_table = PrettyTable()
    manual_individual_table.field_names = [
        'ID',
        'Name',
        'Gender',
        'Birthday',
        'Age',
        'Alive',
        'Death',
        'Child',
        'Spouse',
    ]

    # They should be equal
    assert_equals(str(manual_family_table), str(family_table))
    assert_equals(str(manual_individual_table), str(individual_table))
