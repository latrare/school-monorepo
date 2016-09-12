from ..files import write_result


def bruteforce(trials, passwords, resfile, salt=None):
    cracked = []
    for trial in trials:
        password = ''.join(password if not salt else password + salt)
        sha256 = hashlib.sha256(password.encode('utf-8')).hexdigest()
        if sha256 in passwords:
            for uid in passwords[sha256]:
                cracked.append((password, uid, sha256))
                write_result(resfile, password, uid, sha256)
    return cracked
