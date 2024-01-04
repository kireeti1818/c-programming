#include<stdio.h>
#define MAX_LEN 1000
#define TAB_STOP 4
int main()
{
	char c;
	int i=0;
	char line[MAX_LEN];
	while((c=getchar())!=EOF)
	{
		line[i]=c;
		i++;
	}
	line[++i]='\0';
	i=0;
	int count=0;
	while(line[i]!='\0')
	{
		if(line[i]!='\t')
		{
			count++;
			putchar(line[i]);
		}
		else
		{
			for(int j=0;j<count%TAB_STOP;j++)putchar(' ');
			count=0;
		}
		i++;
	}
	return 0;
}
