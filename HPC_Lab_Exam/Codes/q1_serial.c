/* Code to implement prefix scan using normal serial method */

/* This code contains overheads like printing and timers */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include<time.h>


#define CLK CLOCK_MONOTONIC

/* 
Function to computes the difference between two time instances

Taken from - http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/ 
*/

//helper function time
struct timespec diff(struct timespec start, struct timespec end){
  struct timespec temp;
  if((end.tv_nsec-start.tv_nsec)<0){
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  }
  else{
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}



int main(int argc, char* argv[])
{
    struct timespec start_e2e, end_e2e, start_alg, end_alg, e2e, alg; 
    /* Should start before anything else */
    clock_gettime(CLK, &start_e2e);

    /* Check if enough command-line arguments are taken in. */
    if(argc < 4){
        /* Compare to 4 in parallel code if file input is taken. */
        printf( "Usage: %s n p\np=0 for serial code.", argv[0] );
        return -1;
    }


    // read cmd args
	int n = atoi(argv[1]);		// size of array
	int p = atoi(argv[2]);      // no of processors
	
	FILE *fp = fopen(argv[3], "r"); // opened the file containing data
	
	char *problem_name = "prefix_sum";
    char *approach_name = "double-tree";
	
	// initialize array on which prefix scan is performed
	int *A = (int *) malloc(sizeof(int) * n);
	
	char c;
	int i = 0;
	
	// read input line from file
    while((c = fgetc(fp)) != EOF) {
        if (c != ' ') {
            A[i] = c - 48;          // for a digit string, the corresponding integer is obtained by subtracting 48
            i++;
        }
    }


	// block which performs prefix scan
	
	clock_gettime(CLK, &start_alg);	/* Start the algo timer */
	/* Core algorithm follows */

// serial code is pretty trivial, we simply need to 
// add the previous term to the next term
// it seems inherently serial, and hence
// the parallel algorithm is completely different
	for (i=0; i<(n-1); i++)
	{
		A[i+1] = A[i+1] + A[i];
	}

	/* Core algorithm finished */
    clock_gettime(CLK, &end_alg);	/* End the algo timer */
    /* Ensure that only the algorithm is present between these two
     timers. Further, the whole algorithm should be present. */
    
    /* Should end before anything else (printing comes later) */
    clock_gettime(CLK, &end_e2e);
    e2e = diff(start_e2e, end_e2e);
    alg = diff(start_alg, end_alg);

    /* problem_name,approach_name,n,p,e2e_sec,e2e_nsec,alg_sec,alg_nsec
    */  
    printf("%s,%s,%d,%d,%d,%ld,%d,%ld\n", problem_name, approach_name, n, p, e2e.tv_sec, e2e.tv_nsec, alg.tv_sec, alg.tv_nsec);


    /* Creating output file */
	char outfilename[50];
	strcpy(outfilename, "./output/prefix_sum_double-tree_");
	
	char nstr[10], pstr[2];
	
	// building the file name according to the given format
    sprintf(nstr, "%d", n);
    strcat(outfilename, nstr);
    strcat(outfilename, "_");
    sprintf(pstr, "%d", p);
    strcat(outfilename, pstr);
    strcat(outfilename, "_output.txt");

	FILE *fout = fopen(outfilename, "w");

    // writing result to the output file
    for (i=0; i<n; i++)
	{
		fprintf(fout, "%d ", A[i]);
	}

	return 0;
}
