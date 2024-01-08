#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

void display(char stack[],int ind)
{
    if(ind==0)
    {
        printf("stack is empty\n");
        return ;
    }
    printf("elements in the stack are \n");
    for(int i=0;i<ind;i++)
    {
        printf("%c ",stack[i]);
    }
    printf("\n");
}
void topelement(char stack[],int ind)
{
    printf("top of the stack is %c \n",stack[ind-1]);
}
void clear(char stack[],int *ind)
{
    *ind =0;
}
void swaptoptwo(char stack[],int ind)
{
    char a;
    int top1=ind-1;
    int top2=ind-2;
    a=stack[top1];
    stack[top1]=stack[top2];
    stack[top2]=a;
}
int duplicate(char stack[],int ind,char duplistack[])
{
    for(int i=0;i<ind;i++)
    {
        char c=stack[i];
        duplistack[i]=c;
    }
    return ind;
}
int main()
{
    char stack[MAX_SIZE],duplistack[MAX_SIZE];
    int stackindex=0,duplistackindex=0;
    char c;
    while((c=getchar())!=EOF && stackindex<MAX_SIZE)
    {
        if (c=='\n' || c ==' ' || c=='\t') continue;
        stack[stackindex++]=c;
    }
    display(stack,stackindex);
    swaptoptwo(stack,stackindex);
    display(stack,stackindex);
    topelement(stack,stackindex);
    duplistackindex=duplicate(stack,stackindex,duplistack);
    display(stack,stackindex);
    display(duplistack,duplistackindex);
    clear(stack,&stackindex);
    display(stack,stackindex);
    display(duplistack,duplistackindex);
}
