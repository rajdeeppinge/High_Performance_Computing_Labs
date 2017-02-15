#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

void matrix_multiply(int mat_size, int block_size);

int main()
{
	double start_time = omp_get_wtime();
	
	int mat_size = 32;
	int block_size = 8;
	matrix_multiply(mat_size, block_size);

	double end_time = omp_get_wtime() - start_time;

	printf("total time = %lf\n", end_time);
	return 0;	
}

void matrix_multiply(int mat_size, int block_size)
{
	int *a[mat_size], *b[mat_size], *c[mat_size];
	
	int i;
	for(i = 0; i < mat_size; i++)
	{
		a[i] = (int *) malloc(mat_size*sizeof(int));
		b[i] = (int *) malloc(mat_size*sizeof(int));
		c[i] = (int *) malloc(mat_size*sizeof(int));
	}
	
	int j, k, jout, kout;

	for(i = 0; i < mat_size; i++) 
	{
		for(j = 0; j < mat_size;j++)
		{
			a[i][j] = 1;
			b[i][j] = 1;
			c[i][j] = 1;
		}

	}

	int sum = 0;

	for(kout = 0; kout < mat_size; kout += block_size)
	{
		for(jout = 0; jout < mat_size; jout += block_size)
		{
			for(i = 0; i < mat_size; i++) 
			{
				for(j = jout; j < jout+block_size;j++)
				{
					sum = c[i][j];	
					for(k = kout; k < kout+block_size; k++)
					{
						sum += a[i][k]*b[k][j];
					}

					c[i][j] = sum;
				}
			}
		}
	}

/*	for(i = 0; i < mat_size; i++) 
	{
		for(j = 0; j < mat_size;j++)
		{
			printf("c(%d, %d) = %lf ", i, j, c[i][j]);
		}
		printf("\n");
	}*/
}
