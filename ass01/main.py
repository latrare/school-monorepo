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


def dictionary_worker(resfile, passwords, dictionary, salt=None):
    cracked = []
    for h in passwords:
        if h in dictionary:
            for uid in passwords[h]:
                cracked.append((dictionary[h], uid, h))
                write_result(resfile, dictionary[h], uid, h)
    return cracked


def bruteforce_worker(resfile, passwords, trial, salt=None):
    cracked = []
    for password in trial:
        password = ''.join(password) # Necessary due to how permutations returns
        if salt:
            password += salt
        # TODO: Fix code duplication
        sha256 = hashlib.sha256(password.encode('utf-8')).hexdigest()
        if sha256 in passwords:
            for uid in passwords[sha256]:
                cracked.append(password, uid, sha256)
                write_result(resfile, password, uid, sha256)
    return cracked


def write_result(resfile, plaintext, uid, sha256):
    with open(resfile, 'a+') as result:
        result.write('{}::{}::{}\n'.format(plaintext, uid, sha256))


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

    print('[*] {:,} passwords loaded from file.'.format(len(passwords)))

    # Thread pool lifeguard spin waiting
    start = time.time()
    print('[+] Start datetime: {}'.format(datetime.today().isoformat()))

    cpus = multiprocessing.cpu_count()
    # TODO: Place this whole manager in a separate thread so main thread can keep track of time
    with multiprocessing.Pool(cpus) as pool:
        # 1. Dictionary attack
        print('[*] Preparing dictionary attack...')
        with open('john.txt') as dfile:
            if args.salt:
                dict_hashes = {hashlib.sha256((p.strip() + args.salt).encode('utf-8')).hexdigest(): p.strip() for p in dfile if p.strip()}
            else:
                dict_hashes = {hashlib.sha256(p.strip().encode('utf-8')).hexdigest(): p.strip() for p in dfile if p.strip()}
        print('[*] {:,} hashes pre-computed for dictionary entries.'.format(len(dict_hashes)))

        print('[+] Running dictionary attack...')
        cracked_dict = pool.apply(dictionary_worker, (args.results_file, passwords, dict_hashes, args.salt))
        print('[+] {:,} passwords found using dictionary.'.format(len(cracked_dict)))

        for h in cracked_dict:
            del passwords[h[-1]]
        print('[*] {:,} passwords remaining.'.format(len(passwords)))

        # 2. 1337speak dictionary attack
        print('[*] Preparing dictionary attack...')
        print('[*] {:,} hashes pre-computed for 1337 dictionary substitutions.')
        print('[+] Running 1337-dictionary attack...')
        print('[+] {:,} passwords found using 1337-dictionary.')

        # 3. Bruteforce
'''
        for n in range(1, 7):
            print('[+] Bruteforcing passwords of length: {}'.format(n))

            processes = []
            perms = itertools.product(list(string.printable), repeat=n)
            slicesize = ((len(string.printable) ** n) // cpus) // (10 ** (n - 1))
            while True:
                s = list()
                try:
                    for x in range(slicesize):
                        s.append(next(perms))
                except StopIteration:
                    break
                proc = pool.apply_async(bruteforce_worker, (args.results_file, passwords, tuple(s), args.salt))
                processes.append(proc)

            for p in processes:
                p.get()
'''


if __name__ == '__main__':
    main()
