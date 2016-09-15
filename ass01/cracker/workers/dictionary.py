import hashlib

from ..files import write_result


def dictionary_generate_sha256(dictionary):
    'Generates dictionary of sha256 hashes for list of dictionary words'
    realdict = dict()
    for entry in dictionary:
        sha256 = hashlib.sha256(entry.encode('utf-8')).hexdigest()
        realdict[sha256] = entry

    return realdict


def dictionary(trials, dictionary, resfile, salt=None):
    cracked = []
    for trial in trials:
        sha256 = hashlib.sha256(trial.encode('utf-8'))
        if sha256 in dictionary:
            cracked.append((trial, uid, sha256))
            write_result(trial, uid, sha256)
    return cracked
