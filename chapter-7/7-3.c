#include <stdarg.h>
#include <stdio.h>
void minprintf(char *fmt, ...)
{
    va_list ap; 
    char *p, *sval,cval;
    int ival;
    double dval;
    va_start(ap, fmt); 
    for (p = fmt; *p; p++) 
    {
        if (*p != '%') 
        {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            case 'c':
                cval = va_arg(ap, int);
                printf("%c",cval);
                break;
            case 'o':
                ival = va_arg(ap, int);
                printf("%o", ival);
                break;
            case 'x':
                ival = va_arg(ap, int);
                printf("%x", ival);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); 
}
int main()
{
    int a=2,c=3,b=011;
    minprintf("%d %o %d",a,b,c);
    return 0;
}
