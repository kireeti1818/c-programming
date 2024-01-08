#include <stdio.h>

unsigned invert(unsigned x, int p, int n, unsigned y);

int main()
{
        int va[4],i=0,val;
        char c;
        while((c=getchar())!=EOF)
        {
                int x=c-'0';
                if (c==' ' || c=='\n')
                {
                        va[i++]=val;
                        x=val;
                        val=0;
                }
                else
                {
                        val=val*10+x;
                }

        }
        printf("%d %d %d %d",va[0],va[1],va[2],va[3]);
    printf("%u", setbits((unsigned) va[0],va[1],va[2], (unsigned) va[3]));

}

unsigned invert(unsigned x, int p, int n, unsigned y) {
    unsigned result= x ^ ~(~(~0 << n) << (p + 1 - n));
    return  result;
}

