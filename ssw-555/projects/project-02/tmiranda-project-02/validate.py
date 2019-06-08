'Trevor Miranda'
import argparse
import re

TAGS = {
    0: ['INDI', 'FAM', 'HEAD', 'TRLR', 'NOTE'],
    1: ['NAME', 'SEX', 'BIRT', 'DEAT', 'FAMC', 'FAMS', 'MARR',
                    'HUSB', 'WIFE', 'CHIL', 'DIV'],
    2: ['DATE',]
}
EXPR_REGEX = re.compile(r'^(?P<level>\d+) (?P<tag>\w+)(\s(?P<args>.+))*$');


def validate(line):
    """Validate a line of GEDCOM."""
    match = EXPR_REGEX.match(line)
    level = match.group('level')
    tag = match.group('tag')
    args = match.group('args')
    valid_tag = 'Y' if tag in TAGS[int(level)] else 'N'
    # Check for exceptions
    if valid_tag != 'Y':
        valid_tag = 'Y' if args in TAGS[int(level)] else 'N'
        if valid_tag == 'Y':
            # Swap tag and arguments
            swap = tag
            tag = args
            args = swap
    return (level, tag, valid_tag, args)


def main():
    parser = argparse.ArgumentParser('Validate GEDCOM file.')
    parser.add_argument('gedcom_file', type=argparse.FileType('r'),
                        help='Gedcom file to validate.')
    args = parser.parse_args()
    with args.gedcom_file as f:
        for line in f.readlines():
            line = line.strip('\n')
            print('-->', line)
            validation = validate(line)
            print('<--', '{level}|{tag}|{valid}|{args}'.format(
                level=validation[0], tag=validation[1], valid=validation[2],
                args=validation[3] or ''))


if __name__ == '__main__':
    main()
