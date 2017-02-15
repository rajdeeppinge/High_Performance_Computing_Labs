#include<stdio.h>
#include<omp.h>

void foo()
{
	//printf("Hello, foo!\n");
	int i;
	for(i=0;i<10;i++)
	{
	}
}

void bar()
{
	//printf("Hello, bar!\n");
	int j;
	for(j=0; j<1000; j++)
	{
	}
	foo();
}

void foobar()
{
	int j;
	for(j=0;j<3000;j++)
	{
	}
}

int main()
{
	int i;
	for(i = 0; i<1000000; i++)
		foo();
	for(i=0; i< 1000000; i++)
		bar();
	for(i=0; i< 10000; i++)
		foobar();
	return 0;
}
