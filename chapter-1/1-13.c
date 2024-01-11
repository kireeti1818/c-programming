#include <stdio.h>
#define MAX_LEN 100
int main()
{
    int arr[MAX_LEN];
    for(int i=0;i<MAX_LEN;i++)
    {
        arr[i]=0;
    }
    int state=1,charcount=0,count=0;
    char c;
    for(;(c=getchar())!=EOF;)
    {
        if (state==0 && charcount>0)
        {
            count++;
            arr[charcount]+=1;
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
    count++;
    arr[charcount]+=1;
    for(int i=1;i<MAX_LEN;i++)
    {
        if (arr[i]!=0)
        {
            printf("%3d ",i,arr[i]);
            for(int j=0;j<arr[i];j++)
            {
                putchar('*');
            }
            putchar('\n');
        }
    }
    return 0;
}
