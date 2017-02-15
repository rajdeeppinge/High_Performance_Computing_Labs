#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void matrix_multiply(int mat_size);

int main()
{
	int mat_size = 512;

	double start_time = omp_get_wtime();	
	
	matrix_multiply(mat_size);

	double end_time = omp_get_wtime() - start_time;

	printf("total time = %lf\n", end_time);
	return 0;	
}

void matrix_multiply(int mat_size)
{
	int *a[mat_size], *b[mat_size], *c[mat_size];
	
	int i;
	for(i = 0; i < mat_size; i++)
	{
		a[i] = (int *) malloc(mat_size*sizeof(int));
		b[i] = (int *) malloc(mat_size*sizeof(int));
		c[i] = (int *) malloc(mat_size*sizeof(int));
	}
	
	int j, k;

	for(i = 0; i < mat_size; i++) 
	{
		for(j = 0; j < mat_size;j++)
		{
			a[i][j] = 1;
			b[i][j] = 1;
		}
	}

	double parallel_start = omp_get_wtime();

//	{		
//		
	
	
	for(i = 0; i < mat_size; i++) 
	{
		for(j = 0; j < mat_size;j++)
		{
			c[i][j] = 0;
					
			#pragma omp parallel num_threads(4)
			{
				int temp = 0; 
				# pragma omp for 
				for(k = 0; k < mat_size; k++)
				{
					temp += a[i][k]*b[k][j];
				}
				
				# pragma omp critical
				{
					c[i][j] += temp;
				}
			}
//			printf("c(%d, %d) = %d ", i, j, c[i][j]);
		}
//		printf("\n");
	}
//	}

	printf("NO of flops: %lf\n", (2*mat_size*mat_size*mat_size+1*mat_size*mat_size) / (1000000*(omp_get_wtime() - parallel_start)) );
}
