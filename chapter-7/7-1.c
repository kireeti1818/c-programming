#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	char  *c=argv[0];
	while(*c!='\0') 
	{
		if(islower(*c)) putchar(toupper(*c));
		else if(isupper(*c)) putchar(tolower(*c));
		else putchar(*c);
		c++;
	}
	putchar('\n');
	return 0;
}
