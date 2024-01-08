#include <stdio.h>
#include<ctype.h>
#define MAX_LEN 1000
double atof(char s[])
{
	double val, power;
	int i, sign;
	for (i = 0; isspace(s[i]); i++);
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if(s[i]='e')
	{
		i++;
	}
	int psign;
	psign=(s[i++]== '-') ? -1 :1;
	int p=0;
	for (p = 0; isdigit(s[i]); i++)
		p = 10 * p + (s[i] - '0');
	long long int k=1;
	
	for (int i=0;i<p;i++)
	{
		k*=10;
	}
	if (psign==-1)return sign * val / (power*k);
	else return sign*val*k/power;
}
int main()
{
	char s[MAX_LEN],c;
	int i=0;
	while((c=getchar())!=EOF)
	{
		s[i++]=c;
	}
	s[i]='\0';
	printf("%.10f",atof(s));
}
