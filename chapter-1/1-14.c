#include <stdio.h>
int main()
{
    int arr[26],whitespaces=0,specialchar=0;
    char c;
    for(int i=0;i<26;i++)
    {
        arr[i]=0;
    }
    for(;(c=getchar())!=EOF;)
    {
        if(c==' ' || c=='\n' || c=='\t')
        {
            whitespaces++;
        }
        else if ((c>='a' && c<26+'a') || (c>='A' && c<26+'A'))
        {
            if (c>='a' && c<26+'a')
            {
                arr[c-'a']++;
            }
            else
            {
                arr[c-'A']++;
            }
        }
    }
    for(int i=0;i<26;i++)
    {
        printf("%c ",65+i);
        for(int j=0;j<arr[i];j++)
        {
            putchar('*');
        }
        putchar('\n');
    }
    printf("whitespaces ");
    for(int j=0;j<whitespaces;j++)
    {
        putchar('*');
    }
    printf("\n");
    printf("specialcharcters");
    for(int j=0;j<specialchar;j++)
    {
        putchar('*');
    }
    return 0;
}
