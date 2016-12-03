import os
import re


def get_file_size(path):
    return str(os.stat(path).st_size)


def get_number_of_operations():
    return int(tuple(open(r"number_of_operations.txt", 'r'))[0])


def spl(input):
    return re.split(r'[._]', input)


algos = ('haff', 'shan')
actions = ('', '-d')

f = open('info.csv', 'w')
header = 'name;old_size;new_size;operations;algo;set;action;num\n'
f.write(header)


files = os.listdir('sets')
for filename in files:
    str_to_write = ''
    str_to_write += filename + ';'
    full_path = (os.path.join('sets', filename))
    str_to_write += str(get_file_size(full_path)) + ';'
    beginning = str_to_write
    for algo in algos:
        os.system('./a.out ' + algo + ' ' + full_path)
        str_to_write += get_file_size(
            full_path[:-(len(spl(full_path)) - 1)] + '.' + algo) + ';'
        str_to_write += str(get_number_of_operations()) + ';'
        str_to_write += algo + ';'
        str_to_write += spl(filename)[2] + ';'
        str_to_write += 'c' + ';'
        str_to_write += filename[-5:-4] + '\n'
        f.write(str_to_write)
        str_to_write = beginning


files = os.listdir('sets')
archives_huff = []
archives_shan = []
for value in files:
    if 'haff' in value:
        archives_huff.append(value)

for value in files:
    if 'shan' in value:
        archives_shan.append(value)


for filename in archives_huff:
    str_to_write = ''
    str_to_write += filename + ';'
    full_path = (os.path.join('sets', filename))
    str_to_write += str(get_file_size(full_path)) + ';'
    os.system('./a.out ' + 'haff' + ' -d ' + full_path)
    str_to_write += get_file_size(
        full_path[:-(len(spl(full_path)))] + '-unz-h' + '.' + 'txt') + ';'
    str_to_write += str(get_number_of_operations()) + ';'
    str_to_write += 'haff' + ';'
    str_to_write += spl(filename)[2] + ';'
    str_to_write += 'd' + ';'
    str_to_write += filename[-6:-5] + '\n'
    f.write(str_to_write)


for filename in archives_shan:
    str_to_write = ''
    str_to_write += filename + ';'
    full_path = (os.path.join('sets', filename))
    str_to_write += str(get_file_size(full_path)) + ';'
    os.system('./a.out ' + 'shan' + ' -d ' + full_path)
    str_to_write += get_file_size(
        full_path[:-(len(spl(full_path)))] + '-unz-s' + '.' + 'txt') + ';'
    str_to_write += str(get_number_of_operations()) + ';'
    str_to_write += 'shan' + ';'
    str_to_write += spl(filename)[2] + ';'
    str_to_write += 'd' + ';'
    str_to_write += filename[-6:-5] + '\n'
    f.write(str_to_write)


f.close()
