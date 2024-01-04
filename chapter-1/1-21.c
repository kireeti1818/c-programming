#include<stdio.h>
#define MAX_LEN 1000
#define TAB_STOP 4
int main()
{
	int i;
	char c;
	char line[MAX_LEN];
	for(i=0;(c=getchar())!=EOF;i++)
	{
		line[i]=c;
	}
	line[++i]='\0';
	i=0;
	int count;
	while(line[i]!='\0')
	{
		if(line[i]!=' ')
		{
			for(int j=0;j<count/TAB_STOP;j++)
			{
				putchar('\t');
			}
			for(int j=0;j<count%TAB_STOP;j++)
			{
				putchar(' ');
			}
			count =0;
			putchar(line[i]);
		}
		else
		{
			count++;
		}
		i++;
	}
	return 0;
}
