#include <stdio.h>

int main()
{
    int state=1,charcount=0,count=0;
    char c;
    for(;(c=getchar())!=EOF;)
    {
        if (state==0 && charcount>0)
        {
            count++;
            charcount=0;
        }
        if(c==' ' || c=='\n' || c=='\t')
        {
            state=0;
            
        }
        else
        {
            state=1;
        }
        if(state == 0)
        {
            continue;
        }
        else
        {
            charcount++;
        }
        
    }
    if (state==0 && charcount>0)
        {
            count++;
        }
    printf("%d",count);
    return 0;
}
