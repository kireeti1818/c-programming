#include<stdio.h>
#define MAX_LEN 1000
void squezze(char a[],char b[])
{
	int i,j;

	for(int p=0;a[p]!='\0';p++)
	{
		for(i=j=0;b[i]!='\0';i++)
		{
			if (b[i]!=a[p])
				b[j++]=b[i];
		}
		b[j]='\0';
	}
}

int main()
{
	char s1[MAX_LEN],s2[MAX_LEN],c;
	int i=0;
	for(i=0;(c=getchar())!=' ' && i!='\n' && i!='\t';i++)
		s1[i]=c;
	s1[i]='\0';
	//printf("%s",s1);
	i=0;
	for(i=0;(c=getchar())!=EOF && c!=' ' && i!='\n' && i!='\t';i++)
                s2[i]=c;
        s2[i]='\0';
        squezze(s1,s2);
	printf("%s",s2);
	return 0;
}
