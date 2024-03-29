#!/bin/python
'''
Author: Akshar Varma
Date: 19 November, 2016.
'''
import subprocess
import os
import sys
import maps


def line(n):
    print('-'*n)

USAGE = """
Usage:

run.py problem_name approach_name serial_executable parallel_executable runs

'problem_name' is the name of the problem assigned to you.
'approach_name' is the name of the appraoch assigned to you.
'serial_executable' must be the name of the compiled executable file for the serial code.
'parallel_executable' must be the name of the compiled executable file for the parallel code.
'runs' is the number of times to run the codes. Run at least thrice and ideally 10 times.
"""
if len(sys.argv) < 6:
    print(USAGE)
    exit(0)

README = """
This file will create log files containing the results of the runs for the codes that have been provided.
"""

problem_name = sys.argv[1]
approach_name = sys.argv[2]
serial_executable = sys.argv[3]
parallel_executable = sys.argv[4]

if problem_name not in maps.problem_list:
    print(problem_name, 'not in', maps.problem_list)
    exit(0)

if approach_name not in maps.approaches[problem_name]:
    print(approach_name, 'not a valid approach for', problem_name)
    print('Choose from:')
    print(maps.approaches[problem_name])
    exit(0)


base = os.getcwd()+'/'
log_directory = base + 'logs/'
maps.create_rename_directory(log_directory)

base = os.getcwd()+'/'
output_directory = base + 'output/'
maps.create_rename_directory(output_directory)

line(80)
print('Assuming that input has been created for:', problem_name)
subprocess.call('lscpu > '
                + log_directory
                + "lscpu.txt", shell=True)
subprocess.call('cat /proc/cpuinfo > '
                + log_directory
                + "cpuinfo.txt", shell=True)
runs = int(sys.argv[5])
for run in range(runs):
    print('Run:', run+1)
    print('Running Serial')
    for n in maps.problem_size[problem_name]:
        print('Problem Size:', n)
        input_file = maps.input_directory+'/prefix_sum/'+problem_name+'_'+str(n)+'_input.txt'
        subprocess.call('./' + serial_executable
                        + " " + str(n)
                        + " " + str(0)  # p=0 for serial code.
                        + " " + input_file
                        + " >> " + maps.log_directory
                        + problem_name + "_" + approach_name
                        + ".logs",
                        shell=True)
    line(80)

    print('Running Parallel')
    for p in maps.processor_range:
        print('Number of Processors:', p)
        for n in maps.problem_size[problem_name]:
            input_file = maps.input_directory+'/prefix_sum/'+problem_name+'_'+str(n)+'_input.txt'
            print('Problem Size:', n)
            subprocess.call('./' + parallel_executable
                            + " " + str(n)
                            + " " + str(p)
                            + " " + input_file
                            + " >> " + maps.log_directory
                            + problem_name + "_" + approach_name
                            + ".logs",
                            shell=True)
        # Look into flushing memory
    line(80)


# print('Comparing results')
# subprocess.call('python3 compare.py '+problem_name, shell=True)
# line(80)
