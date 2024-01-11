#include<stdio.h>
#define swap(i,a,b) { i c; c=a;a=b;b=c;}
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    printf("before swap - %d %d \n",a,b);
    swap(int,a,b);
    printf("after swap - %d %d \n",a,b);

    return 0;
}
