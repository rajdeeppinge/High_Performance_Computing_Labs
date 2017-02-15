/* Code to implement prefix scan using tree method. First it uses Forward tree and then uses inverse tree */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<math.h>
#include<string.h>
#include<time.h>

#define CLK CLOCK_MONOTONIC


void scan(int *A, int n, int p)
{	
	int step,i;
	int steplimit = (float)log(n)/(float)log(2);
	int level;
	
	for (level = 1, step=2; level <= steplimit; step=step*2, level++)
	{	
		for (i=step-1;i<n;i=i+step)
		{
			A[i]= A[i] + A[i-step/2];
		}
	}

	step=step/2;
	for (; step>=1; step=step/2)
	{	
		for (i=step-1;i<n;i=i+step)
		{	
			if((i+1)%(step*2) == 0)
				continue;
			else
			{
				A[i] = A[i] + A[i-step];			
			}
		}
	}
}

int main(int argc, char* argv[])
{
    /* Check if enough command-line arguments are taken in. */
    if(argc < 4){
        /* Compare to 4 in parallel code if file input is taken. */
        printf( "Usage: %s n p\np=0 for serial code.", argv[0] );
        return -1;
    }

	int n = atoi(argv[1]);		// size of array
	int p = atoi(argv[2]);      // no of processors
	
	FILE *fp = fopen(argv[3], "r");
	
	char *problem_name = "prefix_sum";
    char *approach_name = "double-tree";
	
	int i = 0;
	
	// initialize array A
	int *A = (int *) malloc(sizeof(int) * n);

	char c;
	
    while((c = fgetc(fp)) != EOF) {
        if (c != ' ') {
            A[i] = c - 48;
            i++;
        }
    }
    
	scan(A, n, p);

	return 0;
}
