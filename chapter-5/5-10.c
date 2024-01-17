#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_VAL 200
int stack[MAX_VAL];
int stack_index=0;
void push(int a)
{
	if(stack_index>=MAX_VAL)
	{
		printf("stack overflow");
		return;
	}
	stack[stack_index]=a;
	//printf("%d\n",stack[stack_index]);
	stack_index++;
}
int pop()
{
	if(stack_index==0)
	{
		printf("stack underflow");
		return 0;
	}
	stack_index--;
	return stack[stack_index];
}
int main(int argc , char * argv[])
{
	/*
	for(int i=0;i<argc;i++)
	{
		printf("%s\t",argv[i]);
	} */
	
	for(int i=1;i<argc;i++)
	{
		char c=*argv[i];
		//printf("%c\n",c);
		if (c>=48 && c<=57)
		{
			//printf("%d\n",c-'0');
			push(c-'0');
		}
		else if(c=='+')
		{
			if(stack_index<2)
			{
				printf("wrong input\n");
				return 0;
			}
			int op1=pop();
			push(pop()+op1);
			
		}
		else if(c=='-')
		{
			if(stack_index<2)
			{
				printf("wrong input\n");
				return 0;
			}
			int op1=pop();
			push(pop()-op1);
			
		}
		else if(c=='x')
		{
			if(stack_index<2)
			{
				printf("wrong input\n");
				return 0;
			}
			int op1=pop();
			push(pop()*op1);
			
		}
		else if(c=='/')
		{
			if(stack_index<2)
			{
				printf("wrong input\n");
				return 0;
			}
			int op1=pop();
			if(op1==0)
			{
				printf("error, zero division");
			}
			else{
			push(pop()/op1);
			}
			
		}
	}
	printf("%d\n",pop());
	
}
