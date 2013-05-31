import re
from itertools import chain


def find_calls(s, r):
    t = re.sub(r'\([^()]+\)', '()', s)
    m = re.findall(r'[\w.]+\(\)', t)
    t = re.sub(r'[\w.]+\(\)', '', t)
    if m==r:
        return
    for i in chain(m, find_calls(t, m)):
        yield i

filename = sys.argv[1]
txt = open(filename, 'r').read().replace('\n', ' ').replace('\t', ' ')
f_list = list(find_calls(txt, []))
print(sorted(list(set(f_list))) })
