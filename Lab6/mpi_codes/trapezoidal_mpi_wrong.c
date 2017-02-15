#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>

double trap_area(double start,int num_cpus, int num_steps,double h);
double f(double x);

int main(int argc,char** argv)
{
	int num_steps = atoi(argv[1]);		// size of array

	printf("%d\n", num_steps);

	int my_rank, num_cpus;      
   	

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

	
	MPI_Comm_size(MPI_COMM_WORLD,&num_cpus);
//printf("cpus:%d\n",num_cpus);
	double start_time = omp_get_wtime();			//to get the start time
	double start=0.0,end=1.0;						// range over which function is integrated
 	   
//int num_steps=10000;		    
    double h=(end-start)/num_steps; 
    
    double area[num_cpus];
	MPI_Status ms;
//printf("Here \n");
	if (my_rank==0)
	{
        	double approx_area= trap_area(my_rank*(end-start)/(double)num_cpus,num_cpus,num_steps, h);
			
		
			int i = 0;
			for(i = 1; i < num_cpus; i++)
			{
				printf("i:%d\n",i);
				MPI_Recv(&area[my_rank],1,MPI_DOUBLE,1,(100-my_rank),MPI_COMM_WORLD,&ms);
				printf("approx area:%lf\n",area[my_rank]);
				approx_area += (double)((area[my_rank]));
			}			
			/*
			MPI_Recv(&approx_area1,1,MPI_DOUBLE,1,99,MPI_COMM_WORLD,&ms);
			MPI_Recv(&approx_area2,1,MPI_DOUBLE,2,98,MPI_COMM_WORLD,&ms);
			MPI_Recv(&approx_area3,1,MPI_DOUBLE,3,97,MPI_COMM_WORLD,&ms);
			*/
	//	printf("approx area:%lf\n",approx_area);
		printf("total area:%lf total time:%lf\n",/*(approx_area + approx_area1+approx_area2+approx_area3)*/approx_area, omp_get_wtime()-start_time);

	}
//printf("Here\n");

	else
	{
		area[my_rank] = trap_area(my_rank*(end-start)/(double)num_cpus,num_cpus, num_steps,h);
			printf("approx area:%lf\n",area[my_rank]);			
MPI_Send(&area[my_rank],1,MPI_DOUBLE,0,(100-my_rank),MPI_COMM_WORLD);
	}
/*
	 if (my_rank==1)
	{
        	double approx_area1= trap_area(my_rank*(end-start)/(double)num_cpus,num_cpus, num_steps,h);
		//	printf("approx area:%lf\n",approx_area1);			
MPI_Send(&approx_area1,1,MPI_DOUBLE,0,99,MPI_COMM_WORLD);

	}
		if (my_rank==2)
	{
        	double approx_area2= trap_area(my_rank*(end-start)/(double)num_cpus,num_cpus, num_steps,h);
			//printf("approx area:%lf\n",approx_area2);
			MPI_Send(&approx_area2,1,MPI_DOUBLE,0,98,MPI_COMM_WORLD);	
} 
	 if (my_rank==3)
	{
        	double approx_area3= trap_area(my_rank*(end-start)/(double)num_cpus,num_cpus,num_steps,h);
		//	printf("approx area:%lf\n",approx_area3);			
MPI_Send(&approx_area3,1,MPI_DOUBLE,0,97,MPI_COMM_WORLD);
	}						// number of trapezoids

	//printf("Approx area is: %f, time_taken = %f\n",approx_area, omp_get_wtime()-start_time);
	
*/


MPI_Finalize();
return 0;
}

double f(double x)
{
	// return the req formula whose integration over given range gives pi
	return 4.0/(1.0+x*x);
}

double trap_area(double start, int num_cpus, int num_steps,double h)
{
	int i;	
	
	double end = start + num_steps/(double)num_cpus;
	double approx = (f(start)+f(end))/2.0;	//adding the area at endpoints beforehand

	
	for (i=1;i<=(num_steps/(num_cpus)-1);i++)
		approx += f(start + i*h);

			

	return approx*h;
}
