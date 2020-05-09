import os
import sys
from copy import deepcopy

def lower_than_zero(x):
    return x < 0

def float_when_str_number(x):
    try:
        x = float(x)
    except:
        return x
    return x

def load_matrix():
    f = open(sys.argv[1], "r")
    matrix = []

    b = f.readline()
    while (b != ""):
        x = b.split(" ")
        x = map(float_when_str_number, x)
        matrix.append(x)
        b = f.readline()
    return matrix

matrix_version = 1
matrix = load_matrix()

result = None
if len(sys.argv) > 2:
    result = open(sys.argv[2], "w+")

def print_matrix(matrix, matrix_version, idx_lowest_row, idx_lowest_col):
    if (idx_lowest_row):
        print("pivot line: " + str(idx_lowest_row))
        print("pivot col: " + str(idx_lowest_col))
        print("")
    print("Matrix " + str(matrix_version) +  ":")
    for i in range(len(matrix)):
        for k in range(len(matrix[i])):
            print(matrix[i][k]),
        if i > 0:
            print("")
    print("")

def print_matrix_csv(matrix, matrix_version, idx_lowest_row, idx_lowest_col):
    if result:
        if (idx_lowest_row):
            print >> result, "pivot line: " + str(idx_lowest_row)
            print >> result, "pivot col: " + str(idx_lowest_col)
            print >> result, ""
        print >> result, "Matrix " + str(matrix_version) +  ":"
        for i in range(len(matrix)):
            for k in range(len(matrix[i])):
                print >> result, matrix[i][k],
                if i > 0 or (i == 0 and (k < len(matrix[0]) - 1)):
                    print >> result, ';',
            if i > 0:
                print >> result, ""
        print >> result, ""

print_matrix(matrix, matrix_version, None, None)
print_matrix_csv(matrix, matrix_version, None, None)

#iterate while there is a negative value in the last line of the matrix
while (len(filter(lower_than_zero, matrix[len(matrix) - 1][1:])) > 0):
    #get the index of the column that contains the lowest value in the last line
    m = matrix[len(matrix) - 1][1:]#1: to skip the first column that contains basic variables
    idx_lowest_col = 1 + m.index(min(m))#1 + to reconsider the first column
    idx_lowest_row = None
    lowest_row_result = float("inf")#infinity
    #divide each element at right hand column by the value at pivot column
    #and find the row that contains the division with lowest result
 
    for i in range(len(matrix) - 2):
        pivot_column_value = matrix[1 + i][idx_lowest_col]
        #rows that are less or equal 0 at divisor(pivot column) must be skipped
        if pivot_column_value <= 0:
            continue
        print(matrix[1 + i][len(matrix[0]) - 1])
        print(pivot_column_value)
        div_res = matrix[1 + i][len(matrix[0]) - 1] / pivot_column_value
        if div_res < lowest_row_result:
            lowest_row_result = div_res
            idx_lowest_row = 1 + i

    #copy the matrix as values will change while old values can be later needed
    matrix_bkp = deepcopy(matrix)

    #put the column identifier at row basic variable
    matrix[idx_lowest_row][0] = matrix[0][idx_lowest_col]

    pivot = matrix_bkp[idx_lowest_row][idx_lowest_col]
    #Each value at the row of lowest division result will be divided by the pivot
    for i in range(len(matrix[0]) - 1):
        matrix[idx_lowest_row][1 + i] /= pivot

    #Each row that is not the row of the pivot value must be updated with 
    #line = line - (value at pivot column * new pivot line computed above)
    for i in range(len(matrix) - 1):
        if (1 + i == idx_lowest_row):#skip this line as it has been computed before
            continue
        for k in range(len(matrix[0]) - 1):
            matrix[1 + i][1 + k] = matrix[1 + i][1 + k] - (matrix_bkp[1 + i][idx_lowest_col] * matrix[idx_lowest_row][1 + k])
    matrix_version += 1
    print_matrix(matrix, matrix_version, idx_lowest_row, idx_lowest_col)
    print_matrix_csv(matrix, matrix_version, idx_lowest_row, idx_lowest_col)
    if matrix_version == 9:
        break

if result:
    result.close()
