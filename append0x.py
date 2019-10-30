#!/usr/bin/env python3

from sys import argv

def read_file_into_list(file_name):
    file = open(file_name, "r+")
    line_data = file.readlines()
    file.close()
    return line_data

def append0x(line_data):
    idx = 0
    for line in line_data:
        line_data[idx] = "0x" + line
        idx += 1
    
    return line_data

def write_lines_to_file(line_data, file_name):
    file = open(file_name, "w+")
    for line in line_data:
        file.write(line)
    
    file.close()


if __name__ == "__main__":
    file_name = argv[1]
    line_data = read_file_into_list(file_name)
    line_data = append0x(line_data)
    write_lines_to_file(line_data, file_name)