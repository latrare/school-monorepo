# Password cracker
# Structure: master thread pool controller that wraps the thread creation, threads report back to controller, controller displays: progress information, duration information, and thread diagnostics
import argparse
import concurrent, concurrent.futures
import itertools
import hashlib
import logging
import os
import threading
import string
import sys
import time


# Default salt value given in assignment PDF
SALT = '_1984'


def main():
    # Parse arguments
    parser = argparse.ArgumentParser(description='Password cracker.')
    parser.add_argument('password_file', help='The file to retrieve the password hashes to crack.')
    parser.add_argument('results_file', help='The file to store the results of the cracking into.')
    parser.add_argument('timeout', help='Number of seconds that cracker should run.')
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
                if not passwords.get(phash):
                    passwords[phash] = [pid,]
                else:
                    passwords[phash].append(pid)

    if not passwords:
        sys.exit('[-] Password file given is empty.')
    else:
        print('[+] Password file successfully parsed.')

    print('[+] {:,} passwords loaded from file.'.format(len(passwords)))

    # Thread pool life guard spin waiting

    with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
        pass

if __name__ == '__main__':
    main()
