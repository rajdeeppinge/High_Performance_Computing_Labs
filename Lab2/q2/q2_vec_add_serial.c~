#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void vector_add(int);

int main()
{
	double start_time = omp_get_wtime();
	
	int vec_size = 100000000;
	vector_add(vec_size);

	double end_time = omp_get_wtime() - start_time;

	printf("total time = %lf\n", end_time);
	return 0;	
}

void vector_add(int vec_size)
{
	int *a = (int *) malloc(vec_size*sizeof(int));
	int *b = (int *) malloc(vec_size*sizeof(int));
	int *c = (int *) malloc(vec_size*sizeof(int));

	printf("Memory allocated successfully\n");

	//double a[vec_size], b[vec_size], c[vec_size];
	int i;

	for(i = 0; i < vec_size; i++) 
	{
		a[i] = i;
		b[i] = i;
	}

	printf("Memory allocated successfully\n");

	double parallel_start = omp_get_wtime();
	for(i = 0; i < vec_size; i++) 
	{
		c[i] = a[i]+b[i];
	}

	printf("time for parallelizable code %lf\n", omp_get_wtime() - parallel_start);
}
