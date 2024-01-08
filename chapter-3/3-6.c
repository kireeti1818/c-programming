#include<stdio.h>
#define MAX_LEN 1000
void itob(int,char[],int,int);
void reverse(char s[]);
int main()
{
	int n;
	scanf("%d",&n);
	char s[MAX_LEN];
	int b,w;
	scanf("%d%d",&b,&w);
	itob(n,s,b,w);
	printf("%s",s);
}
void itob(int n,char s[],int b,int w)
{
	int i=0;
	do
	{
		int k=n%b;
		if (k>9){
			char c= 'A'+k-10;
			s[i++]=c;
		}
		else
		{
			s[i++]='0'+k;
		}
		n=n/b;
	}while(n>0);
	//printf("%d %d",w,i);
	if (w>i)
	{
		for(;i<w;i++)
		{
			s[i]=' ';
		}
	}
	//printf("\n%d\n",i);
	s[i]='\0';
	reverse(s);
}
void reverse(char s[])
	{
		int i=0;
		for(i=0;s[i]!='\0';i++);
		i--;
		int x=0,y=i;
		while(x<=y)
		{
			char c;
			c=s[x];
			s[x]=s[y];
			s[y]=c;
			x++,y--;
		}
	}



