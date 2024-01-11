#include<stdio.h>
#define MAX_LEN 1000
#define LEN80 80
int getlines(char [],int);
void display (char []);
int main()
{
    int len;
	char line[MAX_LEN];
	for(;(len=getlines(line,MAX_LEN))>0;)
	{
		if (len>LEN80)
		{
			printf("STRING = %s, LENGTH = %d",line,len);
		}
	}
	return 0;
}
int getlines(char s[],int lim)
{
    char c;
    int i;
    for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';i++)
	{
		s[i]=c;
	}
	if (c=='\n')
	{
		s[i]='\n';
		i++;
	}
	s[i]='\0';
	return i;
}

