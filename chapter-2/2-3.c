/* Exercise 2-3. Write a function htoi(s) , which converts a string of hexadecimal digits
(including an optional 0x or 0X ) into its equivalent integer value. The allowable digits are 0
through 9 , a through f , and A through F . */
#include<stdio.h>
#define MAX_LEN 100
int main()
{	long int result=0;
	int val=0;
	char input[MAX_LEN],c;
	int i=0;
	for (i=0;(c=getchar())!=EOF;i++)
	{
		input[i]=c;
	}
	input[i]='\0';
	i--;
	int hexa=1;
	while(input[i]!='x' && input[i]!='X' )
	{
		val=input[i]-'0';
		if (val<0 || val>9)
		{
			val=input[i]-'a'+10;
			if (val<10 || val > 15)
			{
				val=input[i]-'A'+10;
			}
		}

		result+=val*hexa;
		hexa*=16;
		i--;
	}
	
	printf("\n%ld",result);
}
