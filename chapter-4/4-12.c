
#include <stdio.h>
#define MAX_LEN 1000
#include<string.h>
void reversestring(char string[])
{
    int last=strlen(string);
    // printf("%d\n",last);
    last--;
    int first=0;
    while(first<last) // by using 2 pointer method we are reversing the string 
    {
        char temp=string[last];
        string[last]=string[first];
        string[first]=temp;
        last--;
        first++;
    }
    
}
void itoa(int num,char string[],int index) //recursively calling itoa function until number is equal to 0
{
    if (num==0)
    {
        string[index]='\0'; // when number is equal to zero we are teriminating and we are reversing the string
        reversestring(string);
        return;
    }
    int k=num%10;
    string[index]='0'+k;
    itoa(num/10,string,++index); 
}
int main()
{
    int num;
    scanf("%d",&num);
    char string[MAX_LEN];
    itoa(num,string,0);
    printf("%s\n",string);
    return 0;
}

