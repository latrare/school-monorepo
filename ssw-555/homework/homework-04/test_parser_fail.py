import lark
from nose.tools import assert_equals, raises

from gedcom.models import *
from gedcom.transformer import GedcomTransformer


TEST_GEDCOM_FAIL = """
0 NOPE Test Note
"""


@raises(lark.exceptions.UnexpectedCharacters)
def test_parser_fail():
    parsetree = (lark.Lark.open('gedcom/gedcom.lark', parser='earley')
                 .parse(TEST_GEDCOM_FAIL))
    tree = GedcomTransformer().transform(parsetree)


def test_parser_fail_empty():
    parsetree = (lark.Lark.open('gedcom/gedcom.lark', parser='earley')
                 .parse(""))
    tree = GedcomTransformer().transform(parsetree)
    assert_equals(tree.children, [])
