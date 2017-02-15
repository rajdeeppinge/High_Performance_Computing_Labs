#include<stdio.h>
#include<omp.h>
#include<math.h>
#include<stdlib.h>

int *k;

int main()
{
  int n = 1e8,i;
  k = (int *)malloc(n*sizeof(int));

  for(i = 0; i<n; i++)
  {
       k[i] = 1;
  }

  //this is parallel for inclusive scan
  float f = log(n)/log(2);
  int g = (int)ceilf(f);
  
  omp_set_num_threads(10);	
  double time1 = omp_get_wtime(); 
  int step,pow;
  int j;
  for(step=0,pow=1;step<g;step++,pow*=2)
  {
  	#pragma omp parallel for
	for(i=n-1;i>=0;i-=pow*2)
	{
		if(i-pow>=0)
			k[i] = k[i] + k[i-pow];
	}
  }
  
  pow = n/4;
  for(step=0;pow>0;step++,pow=pow/2)
  {
  	#pragma omp parallel for
	for(i=2*pow-1;i<n-1;i+=pow*2)
	{
		if(i+pow<n)
			k[i+pow] = k[i+pow] + k[i];
	}
  }
  
  double time2 = omp_get_wtime() - time1;
  
  printf("Parallel Time using tree approach: %0.10lf\n",time2);
  //printf("last element: %d\n",k[n-1]);
}
