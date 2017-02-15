/* Trapezoidal calculation of pi using MPI with MPI_Reduce() */

#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>

double trap_area(double start,int num_cpus, int num_steps,double h);
double f(double x);

int main(int argc,char* argv[])
{
	int my_rank, num_cpus,j;  
	
	float partial_area = 0.0, totalarea = 0.0;

	// start timer before initializing MPI
	double start_time = omp_get_wtime();


	//Initialize MPI
	MPI_Init(&argc,&argv);
	
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	
	MPI_Comm_size(MPI_COMM_WORLD,&num_cpus);

	double start = 0.0, end = 1.0;			// range over which function is integrated
 	int num_steps = atoi(argv[1]);			// number of trapezoids
	   		    
    double h=(end-start)/num_steps; 
	MPI_Status ms;
	
	//calculate the partial_integral in each process
	partial_area = trap_area(my_rank*(end-start)/(double)num_cpus, num_cpus, num_steps, h);

	/* Add up the integrals calculated by each process */
    MPI_Reduce(&partial_area, &totalarea, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	//Part executed by master CPU	
	if (my_rank==0)
	{	                  		
		printf("time: %lf\n",omp_get_wtime()-start_time);
		printf("time: %lf\n",totalarea);
	}

	//finalize and close the MPI
	MPI_Finalize();

	return 0;
}

double f(double x)
{
	// return the req formula whose integration over given range gives pi
	return 4.0/(1.0+x*x);
}

double trap_area(double start, int num_cpus, int num_steps, double h)
{
	int i;	
	
	double end = start + num_steps/(double)num_cpus;	//calculate ending range for this CPU
	double approx = (f(start)+f(end))/2.0;				//adding the area at endpoints beforehand

	//iterate over the assigned range of trapezoids and calculate partial sum
	for (i=1;i<=(num_steps/(num_cpus)-1);i++)
		approx += f(start + i*h);

	return approx*h;
}
