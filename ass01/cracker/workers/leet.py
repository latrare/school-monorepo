from ..files import write_result


'''1337 substitution dictionary, taken from the following sites
(thank you!):

    * http://www.securepasswords.net/site/ASCII-1337-Alphabet/page/23.html
    * <website>
'''
LEET = {
    'a': ['4', '@', '/-\\', '/_\\'],
    'b': ['8', '|3', '|o'],
    'c': ['(', '[', '{', '<', 'k', 's', 'K', 'S'],
    'd': ['|)', 'o|', '|>', '<|', '|)', '|}', '|]'],
    'e': ['3'],
    'f': ['ph', '|='],
    'g': ['(', '9', '6', '[', '-', '[+'],
    'h': ['#', '|-|', '[-]', '{-}', '|=|', '[=]', '{=}', ']-[', '}-{', '(-)', ')-('],
    'i': ['1', 'l', '|', '!', ']['],
    'j': ['_|'],
    'k': ['|<', '/<', '\\<', '|{', '1<'],
    'l': ['1', '|_', '|'],
    'm': ['|\\/|', '^^', '/\\/\\', "|'|'|", '(\\/)', '/\\', '/|\\', '/v\\'],
    'n': ['|\\|', '/\\/', '|\\\\|', '/|/'],
    'o': ['()', '[]', '{}', '0'],
    'p': ['|2', '|D', '|o', '|O', '|>'],
    'q': ['O', '9', '(,)', 'kw'],
    'r': ['|2', '|Z', '|?', '12'],
    's': ['5', '$'],
    't': ['+', "']['", '7'],
    'u': ['|_|'],
    'v': ['|/', '\\|', '\\/', '/'],
    'w': ['\\/\\/', '\\|\\|', '|/|/', '\\|/', '\\^/', '//'],
    'x': ['><', '}{'],
    'y': ['`/', "'/", 'j'],
    'z': ['2', '(/)'],
    '0': ['O', '()'],
    '1': ['L', 'I', '|', ']['],
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


def __traverse_mutation_tree(root, word, path='', paths=[]):
    if word:
        try:
            root.children = [TreeNode(r) for r in LEET[word[0].lower()]]
            root.children.extend([TreeNode(word[0]), TreeNode(word[0].swapcase())])
        except KeyError:
            root.children.append(TreeNode(word[0]))
        for node in root.children:
            __traverse_mutation_tree(node, word[1:], path + node.letter, paths)
    else:
        paths.append(path)
    return paths


def leet_mutate(word):
    with open('resources/leet.txt', 'a') as f:
        root = TreeNode(None)
        for path in __traverse_mutation_tree(root, word):
            if path.strip():
                f.write(path + '\n')
    return None
