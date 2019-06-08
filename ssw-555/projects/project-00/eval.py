import argparse
import datetime

import lark
from prettytable import PrettyTable

from models import Family, Individual
from transformer import GedcomTransformer


def main():
    parser = argparse.ArgumentParser('Gedcom file evaluator')
    parser.add_argument('file', type=argparse.FileType('r'), help='Gedcom file')
    parser.add_argument('-o', '--output', type=argparse.FileType('w'),
                        help='Output file')
    args = parser.parse_args()

    with args.file as f:
        lark_parser = lark.Lark.open('gedcom.lark', parser='earley')
        # Parse the given gedcom file based on the gedcom.lark grammar
        parsetree = lark_parser.parse(f.read())
        # Build the AST
        transformer = GedcomTransformer()
        transformer.transform(parsetree)
        # Get the envionrment from the transformer
        individuals = transformer.individuals
        families = transformer.families
        # Construct individual table
        ind_table = PrettyTable()
        ind_table.field_names = ['ID', 'Name', 'Gender', 'Birthday', 'Age',
                                 'Alive', 'Death', 'Child', 'Spouse']
        for i in sorted(individuals.values(), key=lambda i: i.id_):
            name = '{} /{}/'.format(i.first_name, i.last_name)
            age = (datetime.date.today() - i.birth).days / 365.25
            ind_table.add_row([
                i.id_,
                name,
                i.sex,
                i.birth,
                int(age),
                i.death is None,
                i.death,
                ','.join(i.child_to) or None,
                ','.join(i.spouse_to) or 'N/A'
            ])
        # Construct family table
        fam_table = PrettyTable()
        fam_table.field_names = ['ID', 'Married', 'Divorced', 'Husband ID',
                                 'Husband Name', 'Wife ID', 'Wife Name',
                                 'Children']
        for f in sorted(families.values(), key=lambda f: f.id_):
            wife = [i for i in individuals.values() if i.id_ == f.wife.ref][0]
            wife_name = '{} /{}/'.format(wife.first_name, wife.last_name)
            husband = [i for i in individuals.values()
                       if i.id_ == f.husband.ref][0]
            husband_name = '{} /{}/'.format(husband.first_name,
                                            husband.last_name)
            fam_table.add_row([
                f.id_,
                ','.join(str(m) for m in f.marriages) or 'N/A',
                ','.join(str(d) for d in f.divorces) or 'N/A',
                f.husband.ref,
                husband_name,
                f.wife.ref,
                wife_name,
                ','.join(c.ref for c in f.children) or 'N/A'
            ])
        # TODO: Output table
        if args.output:
            with args.output as f:
                f.write(ind_table)
                f.write('\n')
                f.write(fam_table)
        else:
            print(ind_table)
            print(fam_table)


if __name__ == '__main__':
    main()
