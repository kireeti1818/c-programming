#include <stdarg.h>
#include <stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
char * getword(char *c)
{
    char ch,*chch=c;
    while(!isspace(ch=getchar()))
    {
        *c++=ch;
    }
    *c='\0';
    return chch;
}
void minscanf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int *ival;
    float *dval;
    char st[100];
    va_start(ap, fmt); 

    for (p = fmt; *p; p++) {
        if (*p != '%') 
        {
            continue;
        }

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int *);
                char *d = getword(st);
                sscanf(d, "%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, float *);
                char *f = getword(st);
                sscanf(f, "%f", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                char *s = getword(st);
                //sval = malloc(strlen(s) + 1);
                strcpy(sval, s);
                break;
            case 'o':
                ival = va_arg(ap, int *);
                char *o = getword(st);
                sscanf(o, "%o", ival);
                break;
            case 'x':
                ival = va_arg(ap, int *);
                char *x = getword(st);
                sscanf(x, "%x", ival);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
int main(void) {

    int i,x,o;
    minscanf("%d", &i);
    printf("minscanf input: %d\n", i);
    char a[100];
    minscanf("%s", a);
    printf("minscanf input: %s\n", a);
    float f;
    minscanf("%f", &f);
    printf("minscanf input: %f\n", f);
    minscanf("%o", &o);
    printf("minscanf input in octal %o, in decimal %d\n", o, o);
    minscanf("%x", &x);
    printf("minscanf input in hex %x, in decimal %d\n", x, x);
    return 0;
}
