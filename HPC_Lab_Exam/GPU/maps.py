'''
Author: Akshar Varma
Date: 19 November, 2016.
'''
import os
import subprocess
import random

base = os.getcwd()+'/'
log_directory = base + 'logs/'
input_directory = base + 'input/'
output_validation_directory = base + 'output-validation/'
output_directory = base + 'output/'


problem_list = ['trapezoidal', 'vector', 'matrix_multiplication',
                'pi_using_series', 'image_warping', 'median_filtering',
                'monte_carlo', 'prefix_sum', 'reduction', 'filter']

approaches = {'trapezoidal': ['reduction', 'critical', 'private'],
              'vector': ['static', 'dynamic', 'side-by-side'],
              'matrix_multiplication': ['outermost', 'middle',
                                        'transpose', 'block'],
              'pi_using_series': ['critical', 'reduction',
                                  'pow-function'],
              'image_warping': ['data-division',
                                'collapsed-directive'],
              'median_filtering': ['qsort', 'diff-mem-alloc'],
              'monte_carlo': ['rand', 'rand_r-reduction',
                              'rand_r-critical', 'own-prng'],
              'prefix_sum': ['double-tree', 'data-segmenting'],
              'reduction': ['tree', 'data-segmenting',
                            'segment-tree'],
              'filter': ['double-tree-prefix',
                         'data-segmenting-prefix',
                         'linked-list']}

problem_size = {'trapezoidal': [10**x for x in range(1, 10)],
                'vector': [10**x for x in range(1, 10)],
                'matrix_multiplication': [2**x for x in range(3, 12)],
                'pi_using_series': [10**x for x in range(1, 10)],
                'image_warping': [2**x for x in range(3, 12)],
                'median_filtering': [2**x for x in range(3, 12)],
                'monte_carlo': [10**x for x in range(1, 10)],
                'prefix_sum': [10**x for x in range(1, 9)],
                'reduction': [10**x for x in range(1, 10)],
                'filter': [10**x for x in range(1, 10)]}


# problem_size = {'trapezoidal': [10**x for x in range(1, 4)],
#                 'vector': [10**x for x in range(1, 4)],
#                 'matrix_multiplication': [2**x for x in range(3, 5)],
#                 'pi_using_series': [10**x for x in range(1, 4)],
#                 'image_warping': [2**x for x in range(3, 5)],
#                 'median_filtering': [2**x for x in range(3, 5)],
#                 'monte_carlo': [10**x for x in range(1, 4)],
#                 'prefix_sum': [10**x for x in range(1, 4)],
#                 'reduction': [10**x for x in range(1, 4)],
#                 'filter': [10**x for x in range(1, 4)]}


#processor_range = range(1, 5)
processor_range = [4,8,12,16]

def create_rename_directory(dir_name):
    if not os.path.exists(dir_name):
        subprocess.call("mkdir "+dir_name, shell=True)
    else:
        foo = str(random.randint(0, 10**9))
        print('WARNING!! '+dir_name+' already exists.')
        print('Renaming using ' + foo)
        os.rename(dir_name, dir_name[:-1]+'-renamed-' + foo)
        subprocess.call("mkdir -p "+dir_name, shell=True)
