#include<stdio.h>
int getlen(char []);
int remove_tail(char []);
void reverse(char []);
#define MAX_LEN 1000
int main()
{
	int len;
	char line[MAX_LEN];
	for(;(len=getlen(line))>0;)
	{
		if (remove_tail(line)>0)
		{
			reverse(line);
			printf("%s\n",line);
		}
	}
	return 0;
}
int getlen(char s[])
{
    char c;
    int i;
	for(i=0;i<MAX_LEN-1 && (c=getchar())!=EOF && c!='\n';i++)
	{
		s[i]=c;	
	}
	if(c=='\n')
	{
		s[i]='\n';
		i++;
	}
	s[i]='\0';
	return i;
}
int remove_tail(char c[])
{
    int i=0;
	int len=0;
	while(c[len]!='\0')
	{
		len++;
	}
	len--;
	for (i=len-1;i>0 && (c[i]==' '  || c[i]=='\t');i--);
	if(i>=0)
	{
		i++;
		c[i]='\0';
	}
	return i;
}
void reverse(char c[])
{
	int i=0;
	int len=0;
	char temp;
	while(c[len]!='\0')
	{
		len++;
	}
	len--;
	while(i<=len)
	{
		temp=c[i];
		c[i]=c[len];
		c[len]=temp;
		i++;
		len--;
	}
}
