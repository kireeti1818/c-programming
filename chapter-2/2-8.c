#include<stdio.h>
unsigned rightrot(unsigned x, int n);

int main()
{
        int va[2],i=0,val;
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
        printf("%u",rightrot(va[0],va[1]));
}
unsigned rightrot(unsigned x,  int n)
{
        int k=n%8;
        return (x>>k)||(x<<8-k);

}


