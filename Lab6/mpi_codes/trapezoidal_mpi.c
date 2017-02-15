/* Trapezoidal calculation of pi using MPI */ 

#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>

double trap_area(double start,int num_cpus, int num_steps,double h);
double f(double x);

int main(int argc,char* argv[])
{
	int my_rank, num_cpus,j;      

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

	//Part executed by master CPU	
	if (my_rank==0)
	{	
		double partial_area[num_cpus], totalarea=0.0;		//an array to store component of each element, totalarea variable
		
		//calculate the part assigned to first processor
		partial_area[0]= trap_area(my_rank*(end-start)/(double)num_cpus,num_cpus,num_steps, h);		
		
		totalarea += partial_area[0];

		// iterate over all cpus and receive their partial sums
		for (j=1;j<=(num_cpus-1);j++)
		{
			//receive partial sums
			MPI_Recv(&partial_area[j],1,MPI_DOUBLE,j,(100-j),MPI_COMM_WORLD,&ms);
			
			//add the partial sums to final variable
			totalarea += partial_area[j];
		}
                   		
		printf("time: %lf\n",omp_get_wtime()-start_time);
	}


	//Part executed by other CPUs
	else
	{
		//calculate partial sum
		double approx_area1= trap_area(my_rank*(end-start)/(double)num_cpus, num_cpus, num_steps, h);		
		
		//send partial sum to the master CPU
		MPI_Send(&approx_area1,1,MPI_DOUBLE,0,(100-my_rank),MPI_COMM_WORLD);
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
