'''
Author: Yashwant Keswani & Akshar Varma
Date: 19 November, 2016.
'''

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys


USAGE = """
Usage:

plotter.py log_file

'log_file' is the file containing the logs of the runs that have been done.
"""
if len(sys.argv) < 2:
    print(USAGE)
    exit(0)


filename = sys.argv[1]
dfx = pd.read_csv(filename, header=None,
                 names=['problem_name', 'approach_name',
                        'problem_size', 'n_processor',
                        'e2e_sec', 'e2e_nsec', 'alg_sec', 'alg_nsec'])

dfx['total_e2e_sec'] = dfx['e2e_sec'] + dfx['e2e_nsec']/1000000000
dfx['total_alg_sec'] = dfx['alg_sec'] + dfx['alg_nsec']/1000000000
df = dfx.sort_values(['problem_size', 'n_processor'], ascending = [1, 0])

problem_name = 0
approach_name = 1
problem_size = 2
n_processor = 3
e2e_sec = 4
e2e_nsec = 5
alg_sec = 6
alg_nsec = 7


no_of_sizes = len(df.problem_size.unique())
no_of_processor = len(df.n_processor.unique())
#print(no_of_sizes, no_of_processor)

#The groupby is just like the sql clause
by_problem_size = df.groupby(['problem_size', 'n_processor'])
"""SpeedUp Graph for end to end"""
#There are various functions which can be used instead of mean.
t = by_problem_size['total_e2e_sec'].mean()

""" T will be a series with no_of_processors*no_of_sizes inputs, since we are grouping in this order (problem_size, n_processor), for each problem it will iterate over all the processors """


df3 = np.array(t)
#The values array stores the speedup. Each row corresponds to the number of threads , and the number of columns shows the different problem sizes for each problem statement
values = np.zeros(shape = (no_of_processor, no_of_sizes))
#This loop is used to calculate the speedup
for i in range(no_of_sizes):
	for j in range(no_of_processor):
		#print(df.problem_size.unique()[i], j, df3[i*no_of_processor],df3[i*no_of_processor+j])
		values[j][i] = df3[i*no_of_processor]/df3[i*no_of_processor+j]

plt.figure(1)
#The for loop is used to get all the lines on the same plot
#The label argument is for the legend
for i in range(no_of_processor):
	plt.plot(np.log(df.problem_size.unique()).reshape(df.problem_size.unique().size,1), values[i], label = str(i) + " Thread(s)")
#This is the xlabel
plt.xlabel("log(Problem Size)")
#This is the y_label
plt.ylabel("Speedup")
#Title of the plot
plt.title("SpeedUp vs Problem Size for end to end")
plt.legend(loc = 'upper left')


"""SpeedUp Graph for Algorithm"""

t = None
df3 = None
t = by_problem_size['total_alg_sec'].mean()


df3 = np.array(t)
values = np.zeros(shape = (no_of_processor, no_of_sizes))
for i in range(no_of_sizes):
	for j in range(no_of_processor):
		values[j][i] = df3[i*no_of_processor]/df3[i*no_of_processor+j]
		#print("size = %s and and parallel = %s serial time is = %s"%(i, df3[i*no_of_processor+j], df3[i*no_of_processor]))
plt.figure(2)
s = [str(i) for i in range(no_of_processor)]
xax = np.log(df.problem_size.unique())
xax = xax.reshape(df.problem_size.unique().size,1)
for i in range(no_of_processor):
#	print(i,values[i], xax)
	plt.plot(xax, values[i], label = str(i) + " Thread(s)")
plt.xlabel("log(Problem Size)")
plt.ylabel("Speedup")
plt.title("SpeedUp vs Problem Size for Algorithm")
plt.legend(loc = 'upper left')


"""Time for Algorithm"""

t = None
df3 = None
t = by_problem_size['total_alg_sec'].mean()


df3 = np.array(t)
values = np.zeros(shape = (no_of_processor, no_of_sizes))
for i in range(no_of_sizes):
	for j in range(no_of_processor):
		values[j][i] = df3[i*no_of_processor+j]

plt.figure(3)
s = [str(i) for i in range(no_of_processor)]
for i in range(no_of_processor):
	plt.plot(np.log(df.problem_size.unique()).reshape(df.problem_size.unique().size,1), values[i], label = str(i) + " Thread(s)")
plt.xlabel("log(Problem Size)")
plt.ylabel("Time(in sec)")
plt.title("Algorithm Time(in sec) vs Problem Size for Algorithm")
plt.legend(loc = 'upper left')




"""End to End TIme"""

t = None
df3 = None
t = by_problem_size['total_e2e_sec'].mean()


df3 = np.array(t)
values = np.zeros(shape = (no_of_processor, no_of_sizes))
for i in range(no_of_sizes):
	for j in range(no_of_processor):
		values[j][i] = df3[i*no_of_processor+j]

plt.figure(4)
s = [str(i) for i in range(no_of_processor)]
for i in range(no_of_processor):
	plt.plot(np.log(df.problem_size.unique()).reshape(df.problem_size.unique().size,1), values[i], label = str(i) + " Thread(s)")
plt.xlabel("log(Problem Size)")
plt.ylabel("Time(in sec)")
plt.title("End To End Time (in sec) vs Problem Size for Algorithm")
plt.legend(loc = 'upper left')




"""Efficiency Graph for end to end"""
t = None
df3 = None
t = by_problem_size['total_e2e_sec'].mean()
df3 = np.array(t)
values = np.zeros(shape = (no_of_processor, no_of_sizes))
for i in range(no_of_sizes):
	for j in range(2, no_of_processor):
		values[j][i] = df3[i*no_of_processor]/df3[i*no_of_processor+j]/(j)

plt.figure(5)
s = [str(i) for i in range(no_of_processor)]
for i in range(2, no_of_processor):
	plt.plot(np.log(df.problem_size.unique()).reshape(df.problem_size.unique().size,1), values[i], label = str(i) + " Thread(s)")
plt.xlabel("log(Problem Size)")
plt.ylabel("Efficiency")
plt.title("Efficiency vs Problem Size for end to end")
plt.legend(loc = 'upper left')




"""Efficiency Graph for Algorithm"""
t = None
df3 = None
t = by_problem_size['total_alg_sec'].mean()
df3 = np.array(t)
values = np.zeros(shape = (no_of_processor, no_of_sizes))
for i in range(no_of_sizes):
	for j in range(2,no_of_processor):
		values[j][i] = df3[i*no_of_processor]/df3[i*no_of_processor+j]/(j)

plt.figure(6)
s = [str(i) for i in range(no_of_processor)]
for i in range(2, no_of_processor):
	plt.plot(np.log(df.problem_size.unique()).reshape(df.problem_size.unique().size,1), values[i], label = str(i) + " Thread(s)")
plt.xlabel("log(Problem Size)")
plt.ylabel("Efficiency")
plt.title("Efficiency for Algorithm vs Problem Size")
plt.legend(loc = 'upper left')




"""Karp Flatt for Algorithm"""
t = None
df3 = None
t = by_problem_size['total_alg_sec'].mean()
df3 = np.array(t)
values = np.zeros(shape = (no_of_processor, no_of_sizes))
pinv  = np.zeros(shape = (no_of_processor, no_of_sizes))
for i in range(no_of_sizes):
	for j in range(2, no_of_processor):
		values[j][i] = df3[i*no_of_processor]/df3[i*no_of_processor+j]
		pinv[j][i] = 1/(j)
pinverse = pinv.T
speedupinverse = 1/values.T
plt.figure(7)

karp = (speedupinverse - pinverse)/(1 - pinverse)

karpT2 = karp[:,2:]
pSize = df.problem_size.unique()
lenp = pSize.size

xax = np.linspace(2, stop = no_of_processor-1, num = no_of_processor - 2)
for i in range(5, no_of_sizes):
	plt.plot(xax, karpT2[i], label = "Problem Size = " + str(pSize[i]))
plt.xlabel("Number of Processors")
plt.ylabel("Karp Flatt")
plt.title("Karp Flatt for Algorithm vs Problem Size")
plt.legend(loc = 'upper left')



"""Karp Flatt for End to End"""
t = None
df3 = None
t = by_problem_size['total_e2e_sec'].mean()
df3 = np.array(t)
values = np.zeros(shape = (no_of_processor, no_of_sizes))
pinv  = np.zeros(shape = (no_of_processor, no_of_sizes))
for i in range(no_of_sizes):
	for j in range(2, no_of_processor):
		#print(i, j, df3[i*no_of_processor], df3[i*no_of_processor+j])
		values[j][i] = df3[i*no_of_processor]/df3[i*no_of_processor+j]
		pinv[j][i] = 1/(j)
pinverse = pinv.T
speedupinverse = 1/values.T
plt.figure(8)

karp = (speedupinverse - pinverse)/(1 - pinverse)

karpT2 = karp[:,2:]
pSize = df.problem_size.unique()
#print(speedupinverse)
#print(pinverse)

#print(karpT2)
xax = np.linspace(2, stop = no_of_processor-1, num = no_of_processor - 2)

for i in range(5, no_of_sizes):
	plt.plot(xax, karpT2[i], label = "Problem Size = " + str(pSize[i]))
plt.xlabel("Number of Processors")
plt.ylabel("Karp Flatt")
plt.title("Karp Flatt for End To End vs Problem Size")
plt.legend(loc = 'upper left')


plt.show()
#print(df.head())


