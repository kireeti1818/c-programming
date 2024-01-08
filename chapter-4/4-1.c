#include<stdio.h>
#define MAX_LEN 1000
int strrindex(char[],char[]);
int main()
{
        char s[MAX_LEN],c;
        int i=0;
        while((c=getchar())!='\n')
        {
                s[i++]=c;
        }
        s[i]='\0';
        // printf("%s\n",s);
        char t[MAX_LEN];
        i=0;
        while((c=getchar())!=EOF && c!='\n')
        {
                t[i++]=c;
        }
        t[i]='\0';
        // printf("%s\n",t);
        printf("rightmost index of %s in %s is %d",t,s,strrindex(s,t));
}
int strrindex(char s[],char t[])
{
        int lens=0,lent=0;
        for(;s[lens]!='\0';lens++);
        for(;t[lent]!='\0';lent++);
        // int k=0;
        int k=lens-lent;
        // printf("%d %d %d ",lens,lent,k);
        while(k>=0)
        {
                int p;
                for(p=0;p<lent;p++)
                {
                        if(s[k+p]!=t[p])break;
                }
                // printf("%d\n",p);
                if (p==lent)
                        return k;
                k--;
        }
        return -1;

}
`
