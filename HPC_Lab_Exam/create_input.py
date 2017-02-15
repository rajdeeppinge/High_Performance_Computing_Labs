'''
Author: Akshar Varma
Date: 19 November, 2016.
'''
import numpy as np
import os
import sys
import maps

USAGE = """
Usage:

create_input.py problem_name

'problem_name' is the name of the problem assigned to you.
"""
if len(sys.argv) < 2:
    print(USAGE)
    exit(0)

# Set a seed so that all inputs and outputs are the same.
# This will be changed during on the day of evaluation.
np.random.seed(42)

# Make the directory to keep the input files.
base = os.getcwd()+'/'
input_directory = base + 'input/'
maps.create_rename_directory(input_directory)

# Make the directory to keep the output validation files.
base = os.getcwd()+'/'
output_validation_directory = base + 'output-validation/'
maps.create_rename_directory(output_validation_directory)


def vector(problem_name, problem_input_directory, problem_outval_directory):
    for size in maps.problem_size[problem_name]:
        array1 = np.random.randint(0, 10, size=size)
        array2 = np.random.randint(0, 10, size=size)
        ans = array1*array2
        f = open(problem_input_directory+problem_name+"_"+str(size)+'_input.txt', 'w')
        for i in array1:
            f.write(str(i) + " ")
        for i in array2:
            f.write(str(i) + " ")
        f.close()
        
        f = open(problem_outval_directory+problem_name+"_"+str(size)+"_output.txt", "w")
        f.write(str(ans[0]))
        f.close()


def matrix(problem_name, problem_input_directory, problem_outval_directory):
    for size in maps.problem_size[problem_name]:
        matrix1 = np.random.rand(size, size)
        matrix2 = np.random.rand(size, size)
        ans = np.dot(matrix1, matrix2)
        f = open(problem_input_directory+problem_name+"_"+str(size)+'_input.txt', 'w')
        for each in matrix1:
            f.write(" ".join(map(str, each))+"\n")
        for each in matrix2:
            f.write(" ".join(map(str, each))+"\n")
        f.close()

        f = open(problem_outval_directory+problem_name+"_"+str(size)+"_output.txt", "w")
        for each in ans:
            f.write(" ".join(map(str, each))+"\n")
        f.close()


def prefix(problem_name, problem_input_directory, problem_outval_directory):
    for size in maps.problem_size[problem_name]:
        array = np.random.randint(0, 10, size=size)
        ans = np.cumsum(array)
        f = open(problem_input_directory+problem_name+"_"+str(size)+'_input.txt', 'w')
        for i in array:
            f.write(str(i) + " ")
        f.close()
        f = open(problem_outval_directory+problem_name+"_"+str(size)+"_output.txt", "w")
        for i in ans:
            f.write(str(i) + " ")
        f.close()


def reduction(problem_name, problem_input_directory, problem_outval_directory):
    for size in maps.problem_size[problem_name]:
        array = np.random.randint(0, 10, size=size)
        ans = np.sum(array)
        f = open(problem_input_directory+problem_name+"_"+str(size)+'_input.txt', 'w')
        for i in array:
            f.write(str(i) + " ")
        f.close()
        f = open(problem_outval_directory+problem_name+"_"+str(size)+"_output.txt", "w")
        f.write(str(ans))
        f.close()


def filtering(problem_name, problem_input_directory, problem_outval_directory):
    for size in maps.problem_size[problem_name]:
        k = np.random.randint(0, 10)
        array = np.random.randint(0, 10, size=size)
        ans = array[array > k]
        f = open(problem_input_directory+problem_name+"_"+str(size)+'_input.txt', 'w')
        f.write(str(k)+"\n")
        for i in array:
            f.write(str(i) + " ")
        f.close()
        f = open(problem_outval_directory+problem_name+"_"+str(size)+"_output.txt", "w")
        for i in ans:
            f.write(str(i) + " ")
        f.close()


func_map = {'vector': vector,
            'matrix_multiplication': matrix,
            'prefix_sum': prefix,
            'reduction': reduction,
            'filter': filtering}

problem_name = sys.argv[1]
problem_input_directory = maps.input_directory + problem_name+'/'
maps.create_rename_directory(problem_input_directory)
problem_outval_directory = maps.output_validation_directory + problem_name + '/'
maps.create_rename_directory(problem_outval_directory)

func_map[problem_name](problem_name, problem_input_directory,
                       problem_outval_directory)
