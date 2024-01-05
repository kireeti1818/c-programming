#include<stdio.h>
#define MAX_LEN 1000
int min(int x,int y){
       	if (x>y)
	{
		return y;
	}
	return x;
}
int any1(char a[],char b[])
{
        int i,j,index=MAX_LEN;
        for(int p=0;b[p]!='\0';p++)
        {
                for(i=j=0;a[i]!='\0';i++)
                {
                        if (a[i]==b[p]){
                                index=min(index,i);
				break;}
                }
	}
	return (index==MAX_LEN) ?-1 :index;
}

int main()
{
        char s1[MAX_LEN],s2[MAX_LEN],c;
        int i=0;
        for(i=0;(c=getchar())!=' ' && i!='\n' && i!='\t';i++)
                s1[i]=c;
        s1[i]='\0';
        //printf("%s",s1);
        i=0;
        for(i=0;(c=getchar())!=EOF && c!=' ' && i!='\n' && i!='\t';i++)
                s2[i]=c;
        s2[i]='\0';
	
        int index=any1(s1,s2);
        printf("%d\n",index);
        return 0;
} 
