#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 1000
void entab(char *a,int m, int n)
{
	int k=0;
	int i=0;
	while( i++<m)
	{
		putchar(*a++);
	}
	while(*a!='\0')
	{
		if (*a!=' ')
		{
			if(k!=0)
			{
				int t=k/n;
				int s=k%n;
				for(int i =0;i<t;i++) putchar('\t');
				for(int i =0;i<s;i++) putchar(' ');
			}
			putchar(*a);
			k=0;
		}
		else k++;
		a++;
	}
	printf("\n");
}
void detab(char *a, int m, int n)
{
	int i=0;
	while( i++<m)
	{
		putchar(*a++);
	}
	int tab=0;
	while(*a!='\0')
	{
		if(*a!='\\')
		{
			if(tab==1)
			{
				if(*a=='t')
				{
					for(int i =0;i<n;i++) putchar(' ');
				}
				else
				{
					putchar('\\');
				}
			}
			putchar(*a);
			tab=0;
		}
		else tab=1;
		a++;
	}
	printf("\n");
}
int main(int argc, char *argv[])
{
	char a[1000];
	int i=0;
	char c;
	int m = atoi(argv[2]);
    	int n = atoi(argv[3]);
	if(strcmp(argv[1],"entab")==0)
	{
		while((c=getchar())!='\n')
		{
			a[i]=c;
			i++;
		}
		a[i]='\0';
    		if(m>0)
    		{
    			n=n*-1;
    			entab(a,m,n);
    		}
    		else
    		{
    			m=m*-1;
    			entab(a,n,m);
    		}
    	}
    	else
    	{
    		while((c=getchar())!='\n')
		{
			a[i]=c;
			i++;
		}
		a[i]='\0';
    		if(m>0)
    		{
    			n=n*-1;
    			detab(a,m,n);
    		}
    		else
    		{
    			m=m*-1;
    			detab(a,n,m);
    		}
    	}
    	return 0;
	
}
