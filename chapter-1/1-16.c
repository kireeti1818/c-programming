#include<stdio.h>
int getlines();

int main()
{
    int len;
	int max=0;
	for(;(len=getlines())>0;)
	{
		if (len>max)
		{
			max=len;
		}
	}
	if(max>0)
	{
		printf("\n%d\n",max);
	}
	return 0;
}
int getlines()
{
    char c;
    int i;
    for(i=0; (c=getchar())!=EOF && c!='\n';i++);
	if (c=='\n')
	{
		i++;
	}
	return i;
}
