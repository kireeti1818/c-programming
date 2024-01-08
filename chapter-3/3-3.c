#include<stdio.h>
#define MAX_LEN 1000
void expand(char[],char[]);
int main()
{
        char s1[MAX_LEN],s2[MAX_LEN];
        char c;
        int i=0;
        while((c=getchar())!=EOF)
        {
                s1[i++]=c;
        }
        s1[i]='\0';
        printf("\n%s\n",s1);
        expand(s1,s2);
        printf("\n%s\n",s2);
        return 0;
}
void expand(char s1[],char s2[])
{
        int i=0,j=0;
        int state =0;
        while(s1[i]!='\0')
        {
                if (s1[i]!='-')
                {
                        state=1;
                        s2[j++]=s1[i++];
                }
                else
                {
                        if (state==1)
                        {
                            
                                int t=++i;
                                for(char k= s2[--j]+1;k<=s1[t];k++)
                                {
                                        // printf("%c %c",s2[j]+1,s1[i]);
                                        s2[++j]=k;
                                
                                 }
                        }
                        else
                        {
                                s2[j++]=s1[i++];
                        }
                }


        }
        s2[j]='\0';

}


