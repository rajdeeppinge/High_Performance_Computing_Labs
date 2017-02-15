#include <stdio.h>
#include <omp.h>

double trap_area(double start, double end, int num_steps);
double f(double x);

double global_approx;

int main()
{
	double start_time = omp_get_wtime();
	double start=0.0,end=1.0;
	int num_steps=100;
	double approx_area= trap_area(start,end,num_steps);
	printf("Approx area is: %f, time_taken = %f\n",approx_area, omp_get_wtime()-start_time);
	return 0;
}

double f(double x)
{
	// return the req formula
	return 4.0/(1.0+x*x);
}

double trap_area(double start,double end, int num_steps)
{
	int i;	
	double h= (end-start)/num_steps;

	double approx[omp_get_num_threads()];

	global_approx = (f(start)+f(end))/2.0;

	#pragma omp parallel
	{	int id = omp_get_thread_num();
		approx[id] = 0;
		#pragma omp for
		for (i=1;i<=(num_steps-1);i++)	
			approx[id] += f(start + i*h);
	}

	global_approx = sum_arr(approx);
	return global_approx*h;	
}

double sum_arr(double approx[])
{
	int i, num_threads = omp_get_num_threads();
	for(i=0; i<num_threads(); i++) {
		
	}
}
