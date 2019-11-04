#!/usr/bin/env python3

from sys import argv

def read_file_into_list(file_name):
    """
        Creates a list containing each line of text from the file.

        Arguments:
        file_name -- string containing the path to the file

        Return:
        A list containing each line from the file.
    """
    file = open(file_name, "r+")
    line_data = file.readlines()
    file.close()
    return line_data

def prepend0x(line_data):
    """
        Prepends the string '0x' to the beginning of each line.

        Arguments:
        line_data -- list containing the lines to modify

        Returns:
        A list containing the modified lines
    """
    idx = 0
    for line in line_data:
        line_data[idx] = "0x" + line
        idx += 1
    
    return line_data

def write_lines_to_file(line_data, file_name):
    """
        Writes the list of strings to the specified file.

        Arguments:
        line_data -- list containing the lines to write
        file_name -- string containing the path to the file to write to.
    """
    file = open(file_name, "w+")
    for line in line_data:
        file.write(line)
    
    file.close()


if __name__ == "__main__":
    file_name = argv[1]
    line_data = read_file_into_list(file_name)
    line_data = prepend0x(line_data)
    write_lines_to_file(line_data, file_name)