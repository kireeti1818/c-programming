#include<stdio.h>
#define MAX_LEN 1000
int function(char s[])
{
	int brac=0,flow=0,sq=0;
	int i=0;
	for(;s[i]!='\0';i++);
	if (i==0)return -1;
//	printf("%s",s);
	for(int i=0;s[i]!='\0';i++)
	{
		if(s[i]=='{')
		{
			flow++;
		}
		else if(s[i]=='}')
		{
			flow--;
		}
		else if(s[i]=='[')
                {       
                        sq++;
                }       
                else if(s[i]==']')
                {      
                        sq--;
                }
		else if(s[i]=='(')
                {       
                        brac++;  
                }       
                else if(s[i]==')')
                {       
                        brac--;  
                }
//		printf("%d %d %d \n",brac,flow,sq);
	}
//	printf("%d %d %d ",brac,flow,sq);
	if(brac==0 && flow==0 && sq==0)
	{

		return 1;}
	else{
		return -1;
	}
}

int main()
{
    char s[MAX_LEN],c;
    int i=0;
    while((c=getchar())!='\n')
    {
	    s[i++]=c;
    }
    s[i]='\0';
  //  printf("%s",s);
    if (function(s)==1)
    {
	    printf("balanced");
	}
    else
    {
	    printf("unbalanced");
}

}
