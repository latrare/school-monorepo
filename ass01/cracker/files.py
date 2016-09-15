def parse_password_file(path):
    passwords = dict()
    with open(path) as f:
        for line in f:
            if line.strip():
                _, pid, phash = (p.strip() for p in line.split('::') if p.strip())
                if not passwords.get(phash.lower()):
                    passwords[phash.lower()] = [pid]
                else:
                    passwords[phash.lower()].append(pid)
    return passwords


def parse_dictionary_file(path, salt=None):
    with open(path) as f:
        for line in f:
            line = line.strip()
            if line:
                if salt:
                    yield line + salt
                else:
                    yield line


def write_result(result_file, plaintext, uid, sha256):
    with open(result_file, 'a+') as f:
        f.write('{}::{}::{}\n'.format(plaintext, uid, sha256))
