#include <stdio.h>
#include <omp.h>

double trap_area(double start, double end, int num_steps);
double f(double x);

int main()
{
	double start_time = omp_get_wtime();
	double start=0.0,end=1.0;
	int num_steps=100000000;
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

	double approx = (f(start)+f(end))/2.0;

	#pragma omp parallel for num_threads(200) \
		reduction(+: approx)
	for (i=1;i<=(num_steps-1);i++)
		approx += f(start + i*h);		

	return approx*h;
}
