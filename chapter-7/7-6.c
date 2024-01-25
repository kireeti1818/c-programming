#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fp1,*fp2;
	fp1=fopen("abc.txt","r");
	fp2=fopen("xyz.txt","w");
	char c;
	while((c=fgetc(fp1))!=EOF)     // Read characters from "abc.txt" and write to "xyz.txt"
	{
		fputc(c,fp2);
	}

}
