import hashlib

from ..files import write_result


class Bruteforcer:
    """Class that allows passing of necessary arguments to bruteforcing function
    while still allowing use of imap_unordered() call, which prohibits multiple
    arguments from caller
    """
    def __init__(self, passwords, resfile, salt=None):
        self.passwords = passwords
        self.resfile = resfile
        self.salt = salt

    def bruteforce(self, trial):
        cracked = []
        # Necessary concatenation due to itertools.product() return tuples
        trial = ''.join(trial) if not self.salt else ''.join(trial) + self.salt
        sha256 = hashlib.sha256(trial.encode('utf-8')).hexdigest()
        if sha256 in self.passwords:
            for uid in self.passwords[sha256]:
                cracked.append((trial, uid, sha256))
                write_result(self.resfile, trial, uid, sha256)
        return cracked
