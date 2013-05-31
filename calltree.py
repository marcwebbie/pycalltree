import re
import sys
from itertools import chain


def find_calls(s, r):
    t = re.sub(r'\([^()]+\)', '()', s)
    m = re.findall(r'[\w.]+\(\)', t)
    t = re.sub(r'[\w.]+\(\)', '', t)
    if m==r:
        return
    for i in chain(m, find_calls(t, m)):
        yield i

def to_html(output_name, f_list):
    html_begin = '<!DOCTYPE html><head></head><body><h1>{0}</h1><ul>'.format(output_name)
    html_middle = ''
    html_end =  '</ul></body></ul>'
    for elem in f_list: 
        html_middle += '<li>{0}</li>'.format(elem)
    return html_begin + html_middle + html_end

def to_unique_list(f_list):
    return sorted(list(set(f_list)))

# Begin handling inputs
args = sys.argv[1:]
if len(args) > 0:
    try:
        input_filepath = open(args[0], 'r')
        txt = input_filepath.read().replace('\n', ' ') # Open file and remove whitespace
        f_list = to_unique_list(list(find_calls(txt, [])))

        if len(args) > 1:
            result_filepath = args[1]
            open(result_filepath, 'w').write(to_html('Output', f_list))
            print("saved to -> ", result_filepath) 
        else: 
            for elem in f_list:
                print(elem)
    except FileNotFoundError:
        print("File not found: ", args[0])
    except:
        print("Unexpected error:", sys.exc_info()[0])
        raise
else:
    print('usage: python calltree input_file [output_file]')
