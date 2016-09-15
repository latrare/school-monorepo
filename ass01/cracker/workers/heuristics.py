import hashlib

from ..files import write_result


class Digits:
    def __init__(self, passwords, resfile, salt=None):
        self.passwords = passwords
        self.resfile = resfile
        self.salt = salt

    def heuristic(self, trial):
        cracked = []
        trial = ''.join(trial) + self.salt if self.salt else ''.join(trial)
        sha256 = hashlib.sha256(trial.encode('utf-8')).hexdigest()
        if sha256 in self.passwords:
            for uid in self.passwords[sha256]:
                cracked.append((trial, uid, sha256))
                write_result(self.resfile, trial, uid, sha256)
        return cracked
