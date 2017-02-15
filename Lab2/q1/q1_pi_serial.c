/* Serial code to calculate the value of pi using summation */

#include <stdio.h>
#include <omp.h>

double approx_pi(int k);

//double par_time=0.0;
int main()
{
	double start_time = omp_get_wtime();	// starting time
	int num_steps = 100000000;				// number of steps for summation
	double pi = approx_pi(num_steps);		// function call to calculate pi
	
	double total_time = omp_get_wtime() - start_time;	// total time calculation
	
	printf("Approximate value of pi: %lf, time taken = %lf\n", pi, total_time);

	return 0;
}

/* function to calculate the value of pi by summation of given function */
double approx_pi(int k)
{ 
	int i=0;
	double pi = 0.0;	
  
    double loop_start= omp_get_wtime();		// start time for parallelizable code
	
	// loop which performs summation
	for(i=0; i<=k; i++)
	{
		pi += ( (double)(1-2*(i%2)) )/(2*i+1);	// function which gives alternate +ve or -ve 1 in the numerator
	}

    double par_time = omp_get_wtime() - loop_start;	// end of parallelizable code
	printf("time of parallalizable code: %lf, No. of FLOPS = %f\n", par_time, 6*k/(par_time*1000000));
	
	return 4*pi;
}
