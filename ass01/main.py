# Password cracker
# Structure: master thread pool controller that wraps the thread creation, threads report back to controller, controller displays: progress information, duration information, and thread diagnostics
import argparse
import concurrent, concurrent.futures
from datetime import datetime
import itertools
import hashlib
import logging
import multiprocessing
import os
import threading
import string
import sys
import time


# Default salt value given in assignment PDF
SALT = '_1984'


def bruteforce_worker(passwords, trial):
    hashes = tuple(passwords.keys())
    cracked = []
    for t in trial:
        t = ''.join(t)
        h = hashlib.sha256(t.encode('utf-8')).hexdigest()
        if h in hashes:
            with open('results.txt', 'a+') as results:
                results.write('{}::{}\n'.format(t, h))


def main():
    # Parse arguments
    parser = argparse.ArgumentParser(description='Password cracker.')
    parser.add_argument('password_file', help='The file to retrieve the password hashes to crack.')
    parser.add_argument('results_file', help='The file to store the results of the cracking into.')
    parser.add_argument('timeout', type=int, help='Number of seconds that cracker should run.')
    parser.add_argument('salt', nargs='?', help='Salt to be appended to passwords before hashing')

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
    passwords = dict()
    with open(args.password_file) as passfile:
        for password in passfile:
            if password.strip():
                _, pid, phash = password.split('::')
                phash = phash.strip()
                if not passwords.get(phash.lower()):
                    passwords[phash.lower()] = [pid,]
                else:
                    passwords[phash.lower()].append(pid)

    if not passwords:
        sys.exit('[-] Password file given is empty.')
    else:
        print('[+] Password file successfully parsed.')

    print('[+] {:,} passwords loaded from file.'.format(len(passwords)))

    # Thread pool lifeguard spin waiting
    start = time.time()
    print('[+] Start datetime: {}'.format(datetime.today().isoformat()))
    with multiprocessing.Pool(processes=multiprocessing.cpu_count()) as pool:
        for n in range(1, 7):
            print('[+] Bruteforcing passwords of length: {}'.format(n))
            processes = []
            perms = itertools.permutations(list(string.printable), n)
            permsize = len(string.printable) ** n
            slicesize = ((len(string.printable) ** n) // multiprocessing.cpu_count()) // (10 ** (n - 1))
            while True:
                s = list()
                try:
                    for x in range(slicesize):
                        s.append(next(perms))
                except StopIteration:
                    break
                proc = pool.apply_async(bruteforce_worker, (passwords, tuple(s)))
                processes.append(proc)

            for p in processes:
                p.get()


if __name__ == '__main__':
    main()
