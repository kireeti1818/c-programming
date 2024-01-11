
#include <stdio.h>

void main()
{
    float fran;
    int cel;
    int lower=0,upper=300,step=20;
    cel=lower;
    printf("Celsius to Fahrenheit table.\n");
    while(fran<=upper)
    {
        fran=(5.0/9.0*cel)+32;
        printf("%5d%13.2f\n",cel,fran);
        cel+=step;
    }
}
