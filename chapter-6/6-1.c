#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))
struct key {
    char *word;
    int count;
};
struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};
char ch;  
int unget = 0;

char getch()
{
    if (unget == 1) {
        unget = 0;
        return ch;
    } else {
        return getchar();
    }
}

void ungetch(char c)
{
    ch = c;
    unget = 1;
}
int getword(char *word, int lim)
{
    int com=0;
    int c;
    char *w = word;
    while (isspace(c = getch()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) 
    {
        if(c=='#')while((c=getchar())!='\n');
        else if (c=='/')
        {
            c=getchar();
            if (c=='/')
            {
                while((c=getchar())!='\n');
            }
            else if (c=='*')
            {
                
                while(com!=2)
                {
                    c=getchar();
                    if(c=='*')
                    {
                        com++;
                        c=getchar();
                        if (c=='/')
                        {
                            com++;
                        }
                        else
                        {
                            com=0;
                        }
                    }
                }
            }
        }
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
    {
        if (!isalnum(*w = getch())) {
        	if(*w ! = '_')
         	{
        		ungetch(*w);
        		break;
    		}
    	}
    }
    *w = '\0';
    return word[0];
}
int binsearch(char *word, struct key keytab[], int n) {
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, keytab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    }

    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}
