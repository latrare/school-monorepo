import multiprocessing

from cracker.files import *
from cracker.workers import *


def main():
    dictionary = parse_dictionary_file('resources/john.txt')
    with open('resources/leet.txt', 'w+') as f:
        with multiprocessing.Pool(multiprocessing.cpu_count() * 2) as pool:
            dictionary = filter(lambda x: len(x) < 7, sorted(dictionary, key=lambda x: len(x)))
            for result in pool.imap_unordered(leet_mutate, dictionary):
                pass

    lines = None
    with open('resources/leet.txt', 'r') as f:
        lines = sorted(list(set(f.readlines())), key=lambda x: len(x))

    with open('resources/leet.txt', 'w+') as f:
        for line in lines:
            f.write(line)


if __name__ == '__main__':
    main()
