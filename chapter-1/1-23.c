#include<stdio.h>
#define MAX_LEN 10000
char lines[MAX_LEN];
char c;
void commentskipper()
{
	while((c=getchar())!=EOF && c!='*' );
	if (c==EOF)return;
	else
	{
		c=getchar();
		if (c=='/')
		return;
		else 
		commentskipper();
	}
}
	
int main()
{
	int i=0,count;
	
	while((c=getchar())!=EOF)
	{
		if (c=='/')
		{
			if (count==0)
			{
			count+=1;
			continue;
			}
			else{
				while((c=getchar())!=EOF && c!='\n' )continue;
				count =0;
				lines[i]='\n';
				i=i+1;
			}
		}
		else if(c=='*')
		{
			if (count==1)
			{
				
				commentskipper();
				count =0;
				
			}
		}
		else
		{
			
			if (count==1)
			{
				lines[i]='/';
				i+=1;
				count =0;
			}
			else
			{
				lines[i]=c;
				i+=1;
			}
		}
		
	}
	printf("%s",lines);
	return 0;
	
}
