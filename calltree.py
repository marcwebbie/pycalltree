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

def as_ul(output_name, f_list):
    html_begin = '<!DOCTYPE html><head></head><body><h1>{0}</h1><ul>'.format(output_name)
    html_middle = ''
    html_end =  '</ul></body></ul>'
    for elem in f_list: 
        html_middle += '<li>{0}</li>'.format(elem)
    return html_begin + html_middle + html_end

def run():
    f = open('tap.cpp', 'r') # Open file for reading
    txt = f.read().replace('\n', ' ').replace('\t', ' ') # remove whitespace

    f_list = list(find_calls(txt, []))
    f_list = sorted(list(set(f_list))) # remove duplicates from list and sort

    result_filename = '{}{}'.format(f.name,'.html')
    open(result_filename, 'w').write(as_ul(result_filename, f_list))

run()