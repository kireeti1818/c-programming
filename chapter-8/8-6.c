#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

void * calloc_p(int n, int size)
{
	int nsize=n*size;
	char *p,*q;
	if(p=malloc(nsize));
	{
		q=p;
		for(int i=0;i<nsize;i++)
		{
			*p=0;
			p++;
		}
	}
	return q;
}

int main(int argc , char * argv[])
{
	int *a=NULL;
	int n;
	if(argc==1)
	{
		scanf("%d",&n);
	}
	else
	{
		n=*argv[1];
	}
	a=calloc_p(n,sizeof(a));
	if (a==NULL)
	{
		printf("memory not allocated\n");
	}
	else
	{
		for(int i=0;i<n;i++)
			*(a+i)=i;
		for(int i=0;i<n;i++)
			printf("%d",*(a+i));
	}
	printf("\n");
}