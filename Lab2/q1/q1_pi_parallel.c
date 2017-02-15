/* General parallel code to calculate the value of pi using summation 
	BY using critical
*/

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

/* function to calculate the value of pi by summation of given function using critical and pragma for */
double approx_pi(int k)
{ 
	int i=0;
	double global_pi = 0.0;

	# pragma omp parallel
	{ 	
		double pi = 0;

		# pragma omp for
		// loop which performs summation
		for(i=0; i<=k; i++)
		{
			pi += ( (double)(1-2*(i%2)) )/(2*i+1);	// function which gives alternate +ve or -ve 1 in the numerator
		}
		
		//printf("pi: %f\n", pi);
		
		# pragma omp critical
		{
			global_pi += pi;
		}
	} 	
	return 4*global_pi;
}
