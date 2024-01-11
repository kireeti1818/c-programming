#include<stdio.h>
#define FOLD_LEN 20
#define MAX_LEN 1000
char lines[MAX_LEN];
int getlines(char[]);
int main()
{
	int len;
	for(;(len=getlines())>0)
	{
		char result[FOLD_LEN];
		int p,q=0,count,r=0;
		for (p=0;p!='\0';p++)
		{
			if (lines[p]==' ' || lines[p]=='\t')
			{
				count=1;
				q=p;
				
			}
			if (p>=MAX_LEN)
			{
				if (lines[p]=' ' || lines[p]=='\t')
				{ 
					
					putchar('\n');

				}
				else
				{	
					if (count ==0)
					{
						putchar('\n');
					} 	
					else
					{
						
					}
				}
				count =0;	
			}
			
		}
	}
}
int getlines()
{
	char c;
	int i;
	for(i=0;i<MAX_LEN-1 &&  (c=getchar())!='\n' && c!=EOF;i++)
	{
		lines[i]=c;
	}
	lines[i]='\0';
	return i;
}
