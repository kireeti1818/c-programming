#include <stdio.h>
#include <string.h>
#define MAX_LINE 1000
#define abs(x) ((x> 0) ? (x) : -(x))

void itoa(int, char []);
void reverse(char []);
int main(void) {
    int number;
    char s[MAX_LINE];
    number = -2147483648;
    itoa(number, s);
    printf("%s", s);
    return 0;
}

void itoa(int n, char s[]) 
{
    int i, sign;
    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
	n=n/10;
    } while (n != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
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
