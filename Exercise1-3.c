
#include <stdio.h>

void main()
{
    int fran;
    float cel;
    int lower=0,upper=300,step=20;
    fran=lower;
    printf("Fahrenheit to Celsius table.\n");
    while(fran<=upper)
    {
        cel=5.0*(fran-32)/9.0;
        printf("%6d%15.2f\n",fran,cel);
        fran+=step;
    }
}
