#!/usr/bin/env python3

from os import path
from sys import argv

def read_file_into_list(file_path):
    """
        Creates a list containing each line of text from the file.

        Arguments:
        file_name -- string containing the path to the file

        Return:
        A list containing each line from the file.
    """
    file = open(file_path, "r+")
    line_data = file.readlines()
    file.close()
    return line_data
    
def split_data(line_data):
    """
        Splits the lines into the hex string and data string.

        Arguments:
        line_data -- list of strings to parse

        Return:
        A map of the line_data
    """
    data_dict = {}

    for line in line_data:
        # Split each line at the comma
        data_pair = line.split(",")
        data_dict[data_pair[0]] = data_pair[1]

    return data_dict

def make_header_guard(file_path):
    split_path = file_path.split(path.sep)
    base_name = split_path[-1] # The very last entry should be the file name

    base_name = base_name.split(".")
    base_name = base_name[0]

    base_name = base_name.upper() + "_HPP"

    header_guard = "#ifndef " + base_name + "\n#define " + base_name + "\n"
    header_guard += "\n#include <map>\n#include<string>"

    return header_guard

def write_data_to_file(data_dict, map_name, file_path):
    # Set up the header guard.
    header_guard = make_header_guard(file_path)
    out_file = open(file_path, "w+")

    out_file.write(header_guard)

    out_file.write("\n\nstatic std::map<const uint8_t, const std::string> " + map_name)
    out_file.write(" {\n")

    # Write each data set from the dictionary
    i = 0
    for key in data_dict:
        data = data_dict[key].rstrip()
        out_string = "\t{" + str(key) + ",\"" + str(data) + "\"}"
        if i < len(data_dict):
            out_string += ",\n"
        else:
            out_string += "\n"

        out_file.write(out_string)
        i += 1

    # close the map and end the file
    out_file.write("};\n\n#endif")

    out_file.close() 

if __name__ == "__main__":
    file_path = argv[1]
    line_data = read_file_into_list(file_path)
    data_dict = split_data(line_data)
    write_data_to_file(data_dict, "hold", "out.hpp")
