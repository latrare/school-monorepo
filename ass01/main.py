import argparse
from datetime import datetime
import itertools
import multiprocessing
import os
import string
import threading
import time
import sys

from cracker.workers import *
from cracker.files import *
from cracker.util import *


def main():
    # Parse arguments
    parser = argparse.ArgumentParser(description='Password cracker.')
    parser.add_argument('password_file',
                        help='The file to retrieve the sha256 hashes to crack.')
    parser.add_argument('results_file',
                        help='The file to store the results into.')
    parser.add_argument('timeout', type=int,
                        help='Number of seconds that cracker should run.')
    parser.add_argument('salt', nargs='?', default=None,
                        help='Salt to be appended to passwords before hashing')
    args = parser.parse_args()

    if not os.path.exists(args.password_file):
        sys.exit('[-] Password file given does not exist.')
    if not os.path.exists(args.results_file):
        # Create file if it does not yet exist
        with open(args.results_file, 'w+'):
            pass
    if not args.salt:
        print('[-] No salt argument provided. Passwords will not be salted.')

    # Parse in password hash list
    passwords = parse_password_file(args.password_file)
    if not passwords:
        sys.exit('[-] Password file given is empty.')
    print('[*] {:,} passwords loaded from file.'.format(len(passwords)))

    # Clear results file
    with open(args.results_file, 'w+'):
        pass

    # Load in dictionary
    dictionary = generate_dictionary(
                    parse_dictionary_file('resources/john.txt'), salt=args.salt)
    dictionary_leet = generate_dictionary(
                    parse_dictionary_file('resources/leet.txt'), salt=args.salt)

    # Mark start time
    start = time.time()
    print('[+] Start datetime: {}'.format(datetime.today().isoformat()))

    cpu_count = multiprocessing.cpu_count()
    # Create process executor for concurrency support
    with multiprocessing.Pool(cpu_count * 2) as executor:
        ### DICTIONARY OPERATION ###
        print('[+] Beginning dictionary attack...')
        found = []
        for sha256 in passwords:
            if sha256 in dictionary:
                print('[*] Dictionary found: {}'.format(dictionary[sha256]))
                found.append(sha256)
                for uid in passwords[sha256]:
                    write_result(args.results_file, dictionary[sha256], uid, sha256)
        # Remove found entries from unknown passwords
        for sha256 in found:
            del passwords[sha256]
        print('[-] Dictionary attack completed.')

        ### LEET DICTIONARY OPERATION ###
        print('[+] Beginning 1337 dictionary heuristic attack...')
        found = []
        for sha256 in passwords:
            if sha256 in dictionary_leet:
                print('[*] Leet dictionary found: {}'
                      .format(dictionary_leet[sha256]))
                found.append(sha256)
                for uid in passwords[sha256]:
                    write_result(args.results_file, dictionary[sha256], uid,
                                 sha256)
        # Remove found entries from unknown passwords
        for sha256 in found:
            del passwords[sha256]
        print('[-] 1337 dictionary heuristic attack completed.')

        ### DIGIT HEURISTIC OPERATION ###
        print('[+] Beginning digit heuristic attack...')
        found = []
        results_all = []
        digit_gens = list(itertools.product(list(string.digits), repeat=n)
                          for n in range(1, 7))
        for gen in digit_gens:
            digits = Digits(passwords, args.results_file, args.salt)
            results_all.append(executor.imap_unordered(digits.heuristic, gen, 10000))
        for results in results_all:
            for result in results:
                if result:
                    found.append(result[0][-1])
                    print('[*] Digit heuristic found: {}'.format(result[0][0]))
        # Remove found entries from unknown passwords
        for sha256 in found:
            del passwords[sha256]
        print('[-] Digit heuristic attack completed.')

        ### BRUTEFORCE OPERATION ###
        print('[+] Beginning bruteforce attack...')
        # Bruteforce ASCII character cross product generators
        results_all = []
        brute_perm_gens = {n : itertools.product(tuple(string.printable),
                                                 repeat=n)
                           for n in range(1, 7)}
        for n, gen in brute_perm_gens.items():
            bruteforcer = Bruteforcer(passwords, args.results_file, args.salt)
            results_all.append(executor.imap_unordered(bruteforcer.bruteforce,
                                gen, 100000))

        for results in results_all:
            for result in results:
                if result:
                    found.append(result[0][-1])
                    print('[*] Bruteforced: {}'.format(result[0][0]))
        print('[-] Bruteforce attack completed.')


if __name__ == '__main__':
    main()
