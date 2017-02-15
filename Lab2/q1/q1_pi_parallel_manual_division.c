/* Parallel code to calculate the value of pi using summation by reduction and manually dividing work among threads */

#include <stdio.h>
#include <omp.h>

double approx_pi(int k);

int main()
{
	double start_time = omp_get_wtime();	// starting time
	int num_steps = 100000000;				// number of steps for summation
	double pi = approx_pi(num_steps);		// function call to calculate pi
	
	double total_time = 0.0;				// total time calculation
	total_time = omp_get_wtime() - start_time;
	
	printf("Approximate value of pi: %f, time taken = %f\n", pi, total_time);

	return 0;
}

/* function to calculate the value of pi by summation of given function using reduction and pragma for */
double approx_pi(int k)
{ 
	int i=0;
	double global_pi = 0.0;

	double pi = 0.0;
	
	# pragma omp parallel private(pi)
	{
		int num_threads = omp_get_num_threads();
		//printf("threads: %d\n",num_threads);
	
		int id = omp_get_thread_num();
		int istart = (id * k) / num_threads;
		int iend = ((id+1) * k) / num_threads;
		
		//printf("id : %d, start : %d, end : %d\n", id, istart, iend);
		pi = 0.0;
		
		printf("pi before: %f\n", pi);
		
		for(i = istart; i < iend; i++)
		{
			pi += ( (double)(1-2*(i%2)) )/(2*i+1);	// function which gives alternate +ve or -ve 1 in the numerator
		}
		
		printf("pi : %f\n", pi);
		
		#pragma omp critical
		{
			global_pi += pi;
		}
		printf("global : %f\n",global_pi);
	}
		
	return 4*global_pi;
}
