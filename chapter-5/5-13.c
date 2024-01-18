#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_Lines 1000
int main( int argc , char * argv[])
{ 
    int line_size=10;
    if (argc==2) line_size=(*argv[1]-'0');
      //printf("%d %d",argc,line_size);
    char line[1000];
    char *p[MAX_Lines];
    int i=0,j=0;
    char c;
    while((c=getchar())!=EOF)
    {
        if(c=='\n')
        {
            line[i]='\0';
            i=0;
            p[j] = malloc(strlen(line) + 1);
            strcpy(p[j], line);
            j++;
            continue;
        }
        else{
        line[i]=c;
        }
        i++;
    }
    int k= j-line_size;
    if (k<0) k=0;
    while(*(p+k)!=NULL){
        printf("%s\n",*(p+k));
        k++;
    } 
    return 0;
}

