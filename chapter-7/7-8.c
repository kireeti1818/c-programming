#include<stdio.h>
#include<stdlib.h>
int main()
{
	int line = 0,page=1,pr=0;
	FILE *fp;
	fp=fopen("pqr.txt","r");
	char c;
	while((c=fgetc(fp))!=EOF)
	{
		if (line==0 && pr==0)
		{
			printf("\n---START OF PAGE %d---\n\n",page);
			pr=1;
		}
		if(c=='\n') line++;
		putchar(c);
		if(line==5) 
		{
			printf("\n---END OF PAGE %d---\n",page);
			line =0;
			pr=0;
			page++;
		}
	}

}