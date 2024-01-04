#include<stdio.h>
float frantocel(int);
int main()
{
	for(int i=0;i<=300;i+=20)
	{
		printf("%3d %10.2f\n",i,frantocel(i));
	}
	return 0;
}
float frantocel(int fran)
{
	return (5.0/9.0)*(fran-32.0);
}
