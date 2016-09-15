import hashlib

from ..files import write_result


'''1337 substitution dictionary, taken from the following sites
(thank you!):

    * http://www.secureasswords.net/site/ASCII-1337-Alphabet/page/23.html
    * <website>
'''
LEET = {
    'a': ['4', '@'],
    'b': ['8'],
    'e': ['3'],
    'f': ['ph'],
    'g': ['9', '6'],
    'h': ['#'],
    'i': ['1', 'l', '|', '!'],
    'l': ['1', '|'],
    'o': ['0'],
    'q': ['O', '9', 'kw'],
    's': ['5', '$'],
    't': ['+', '7'],
    'z': ['2'],
    '0': ['O', '()'],
    '1': ['l', 'I', '|'],
    '2': ['Z'],
    '3': ['E'],
    '4': ['A'],
    '5': ['S'],
    '6': ['G'],
    '7': ['T'],
    '8': ['B'],
    '9': ['G']
}


class TreeNode:
    def __init__(self, letter):
        self.letter = letter
        self.children = []


def __traverse_mutation_tree(root, word, path='', paths=set()):
    if word:
        try:
            root.children = [TreeNode(r) for r in LEET[word[0].lower()]]
            root.children.extend([TreeNode(word[0]), TreeNode(word[0].swapcase())])
        except KeyError:
            root.children.append(TreeNode(word[0]))
        for node in root.children:
            __traverse_mutation_tree(node, word[1:], path + node.letter, paths)
    else:
        paths.update(set([path]))
    return paths


def leet_mutate(word):
    print(word)
    with open('resources/leet.txt', 'a') as f:
        root = TreeNode(None)
        for path in __traverse_mutation_tree(root, word):
            if path.strip():
                f.write(path + '\n')
    return None


class Leet:
    def __init__(self, passwords, resfile, salt=None):
        self.passwords = passwords
        self.resfile = resfile
        self.salt = salt

    def heuristic(self, word):
        cracked = []
        word = word.strip() + self.salt if self.salt else word.strip()
        sha256 = hashlib.sha256(word.encode('utf-8')).hexdigest()
        if sha256 in self.passwords:
            cracked.append((word, sha256))
            for uid in self.passwords[sha256]:
                write_result(self.resfile, word, uid, sha256)
        return cracked
