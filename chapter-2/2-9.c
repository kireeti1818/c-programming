#include <stdio.h>
int bitcount(unsigned x);

int main() {
	unsigned val=120,x;
       int i;	
       x=val;
	for (i = 0; x != 0; x &= x - 1)
        ++i;
	printf(" %d\n",val, i);
}

	
