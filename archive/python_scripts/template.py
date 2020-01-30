# ------------------------------------------------------------------------- #
# This is template file to show how to format your code; you don't have to  #
# follow it exactly but try to if possible! It makes debugging code and     #
# adding new functions much easier.                                         #
#                                                                           #
# We'll be using the Google Docstrings code style here!                     #
# Always keep lines to < 80 characters                                      #
# Use 4 spaces as tabs; not two, not the \t character                       #
# Include a space after # when writing comments                             #
#                                                                           #
# https://realpython.com/documenting-python-code/                           #
# https://github.com/google/styleguide/blob/gh-pages/pyguide.md             #
# https://docs.python-guide.org/writing/style/                              #
# ------------------------------------------------------------------------- #

# ------------------------------------------------------------------------- #
# About whitespaces (taken from google styleguide)                          #
#                                                                           #
# No whitespace inside parentheses, brackets or braces.                     #
# No whitespace before a comma, semicolon, or colon. Do use whitespace      #
# after a comma, semicolon, or colon, except at the end of the line.        #
#                                                                           #
# Yes: spam(ham[1], {eggs: 2}, [])                                          #
# No:  spam( ham[ 1 ], { eggs: 2 }, [ ] )                                   #
# ------------------------------------------------------------------------- #


# Import statements at top of file
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# This is a sample function, always try to include docstrings as shown
# below to improve readability! If the function is really simple, including
# the first summary line is fine too


def get_spreadsheet_columns(file_loc, print_cols=False):
    """Gets and prints the spreadsheet's header columns

    Args:
        file_loc (str): The file location of the spreadsheet
        print_cols (bool): A flag used to print the columns to the console
            (default is False)

    Returns:
        list: a list of strings representing the header columns

    Raises:
        IOError: Some error description here
    """
    file_data = pd.read_excel(file_loc)
    col_headers = list(file_data.columns.values)

    if print_cols:
        print("\n".join(col_headers))

    return col_headers


def drop_tables(table_loc):
    # TODO(jqp): Implement function here
    return
