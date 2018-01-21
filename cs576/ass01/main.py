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

    # Mark start time
    start = datetime.today()
    print('[+] Start datetime: {}'.format(datetime.today().isoformat()))

    cpu_count = multiprocessing.cpu_count()
    # Create process executor for concurrency support
    def run_cracker(stat):
        stat[0] = 0 # Tried
        stat[1] = 0 # Cracked
        with multiprocessing.Pool(cpu_count * 2) as executor:
            ### DICTIONARY OPERATION ###
            print('[+] Beginning dictionary attack...')
            found = []
            for sha256 in passwords:
                stat[0] += 1
                if sha256 in dictionary:
                    print('[*] Dictionary found: {}'.format(dictionary[sha256]))
                    found.append(sha256)
                    for uid in passwords[sha256]:
                        write_result(args.results_file, dictionary[sha256], uid,
                                     sha256)
            # Remove found entries from unknown passwords
            for sha256 in found:
                del passwords[sha256]
            stat[1] += len(found)
            print('[-] Dictionary attack completed.')

            ### LEET DICTIONARY OPERATION ###
            print('[+] Beginning leet dictionary heuristic attack...')
            found = []
            with open('resources/leet.txt') as dictionary_leet:
                leet = Leet(passwords, args.results_file, args.salt)
                results = executor.imap_unordered(leet.heuristic,
                                                  iter(dictionary_leet),
                                                  chunksize=1000)
                for result in results:
                    stat[0] += 1
                    if result:
                        print('[*] Leet dictionary found: {}'.format(result[0][0]))
                        found.append(result[0][-1])
            # Remove found entries from unknown passwords
            for sha256 in found:
                del passwords[sha256]
            stat[1] += len(found)
            print('[-] Leet dictionary heuristic attack completed.')

            ### DIGIT HEURISTIC OPERATION ###
            print('[+] Beginning digit heuristic attack...')
            found = []
            results_all = []
            digit_gens = list(itertools.product(list(string.digits), repeat=n)
                            for n in range(1, 7))
            for gen in digit_gens:
                digits = Digits(passwords, args.results_file, args.salt)
                results_all.append(executor.imap_unordered(digits.heuristic, gen, chunksize=1000))
            for results in results_all:
                for result in results:
                    stat[0] += 1
                    if result:
                        found.append(result[0][-1])
                        print('[*] Digit heuristic found: {}'.format(result[0][0]))
            # Remove found entries from unknown passwords
            for sha256 in found:
                del passwords[sha256]
            stat[1] += len(found)
            print('[-] Digit heuristic attack completed.')

            ### DICTIONARY + DIGIT HEURISTIC ###
            print('[+] Beginning dictionary+digits heuristic attack...')
            found = []
            for _, word in dictionary.items():
                onecombos = itertools.product(list(''.join(t) for t in itertools.product(tuple(string.digits))), [word])
                twocombos = itertools.product(list(''.join(t) for t in itertools.product(tuple(string.digits), repeat=2)), [word])
                for first, second in itertools.chain(onecombos, twocombos):
                    prepend = first + second
                    append = second + first
                    for combo in (prepend, append):
                        stat[0] += 1
                        sha256 = hashlib.sha256(combo.encode('utf-8'))
                        if sha256 in passwords:
                            found.append(sha256)
                            print('[*] Dictionary+digit heuristic found: {}'.format(combo))
                            for uid in passwords[sha256]:
                                write_result(args.results_file, combo, uid, sha256)
            # Remove found entries from unknown passwords
            for sha256 in found:
                del passwords[sha256]
            stat[1] += len(found)
            print('[-] Dictionary+digits heuristic attack completed.')

            ### BRUTEFORCE OPERATION ###
            print('[+] Beginning bruteforce attack...')
            # Bruteforce ASCII character cross product generators
            results_all = []
            brute_perm_gens = {n : itertools.product(tuple(string.ascii_lowercase + string.digits),
                                                    repeat=n)
                            for n in range(1, 7)}
            for n, gen in brute_perm_gens.items():
                bruteforcer = Bruteforcer(passwords, args.results_file, args.salt)
                results_all.append((n, executor.imap_unordered(bruteforcer.bruteforce,
                                                               gen, chunksize=1000)))

            for results in results_all:
                if results:
                    print('[*] Bruteforcing length {}...'.format(results[0]))
                    results = results[1]
                    for result in results:
                        stat[0] += 1
                        if result:
                            found.append(result[0][-1])
                            stat[1] += 1
                            print('[*] Bruteforced: {}'.format(result[0][0]))
            print('[-] Bruteforce attack completed.')

    stats = multiprocessing.Array('i', (0, 0, 0), lock=False)
    proc = multiprocessing.Process(target=run_cracker, args=(stats,))
    proc.start()
    
    # Keep checking for timeout passage
    while True:
        if (datetime.today() - start).seconds // 60 >= args.timeout:
            proc.terminate()
            time.sleep(0.25)
            print('\n\n')
            print('If you just saw BrokenPipeError exceptions, ignore them.')
            print('They are the result of a non-graceful termination of the cracker process pool.')
            break
        time.sleep(1)

    print('\nCracker statistics:')
    print('-------------------')
    duration = datetime.today() - start
    print('Total duration: {} minutes {} seconds'.format(duration.seconds // 60, duration.seconds % 60))
    print('Passwords tried: {}'.format(stats[0]))
    print('Passwords cracked: {}'.format(stats[1]))


if __name__ == '__main__':
    main()
