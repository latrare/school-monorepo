from ..files import write_result


def dictionary_worker(trials, dictionary, resfile, salt=None):
    cracked = []
    for trial in trials:
        sha256 = hashlib.sha256(trial.encode('utf-8'))
        if sha256 in dictionary:
            cracked.append((trial, uid, sha256))
            write_result(trial, uid, sha256)
            
    return cracked
