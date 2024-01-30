#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 100

int stack[MAXLINE];
int ind = 0;

void push1(int val)
{
    stack[ind] = val;
    printf("%d \n",stack[ind]);
    ind++;
}
	
int pop1()
{
    ind--;
    return stack[ind];
}

int main()
{
    char ch;
    int val = 0,num=0; 

    while (scanf("%c", &ch) != EOF && ch != '\n') 
    {
        int a;
        
        switch (ch)
        {
            case '+':
                if (num==1)
                {
                    push1(val);
                    num=0;
                }
                a = pop1();
                push1(pop1()+a);
                break;
            case '-':
                if (num==1)
                {
                    push1(val);
                    num=0;
                }
                a = pop1();
                push1(pop1()-a);
                break;
            case '*':
                if (num==1)
                {
                    push1(val);
                    num=0;
                }
                a = pop1();
                push1(pop1()*a);
                break;
            case '/':
                if (num==1)
                {
                    push1(val);
                    num=0;
                }
                a = pop1();
                if (a == 0)
                    printf("zero division\n");
                else
                    push1(pop1()/a);
                break;
            case '%':
                if (num==1)
                {
                    push1(val);
                    num=0;
                }
                a = pop1();
                if (a == 0)
                    printf("zero division\n");
                else
                    push1(pop1()%a);
                break;
            case ' ':
                if (num==1)
                {
                    push1(val);
                    num=0;
                }
                val = 0;
                break;
            default:
                if (isdigit(ch))
                {   
                    num=1;
                    val=val*10+(ch-'0');
                }
                else
                {
                    printf("unknown operator\n");
                }
                break;
        }
    }

    printf("Result: %d\n", pop1());

    return 0;
}
