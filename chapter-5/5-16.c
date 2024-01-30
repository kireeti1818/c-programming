#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>
#define MAXLINES 5000
int dic= 0,rev=0,fold=0;
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines) {
    char line[MAXLINES];
    int i = 0, j = 0;
    char c;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line[i] = '\0';
            i = 0;
            lineptr[j] = malloc(strlen(line) + 1);
            strcpy(lineptr[j], line);
            j++;
            continue;
        } else {
            line[i] = c;
        }
        i++;
    }

    return j;
}

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int strcmp1 (char *s1,char *s2)
{
	if(dic) {
		while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
			++s1;
		while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
			++s2;
	}
	while(fold ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2)) {
		if(*s1 == '\0')
			return 0;
		++s1;
		++s2;
		if(dic) {
			while(!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
				++s1;
			while(!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
				++s2;  
		}
	}
	return fold ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2);
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void reverse(void **a)
{
    void **b = a;
    while (*a != NULL)
        a++;
    a--;
    while (b < a)
    {
        void *c = *a;
        *a = *b;
        *b = c;
        b++;
        a--;
    }
}

void qsort1(void *v[], int left, int right, int (*comp)(void *, void *)) 
{
    int i, last;

    if (left >= right) return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    qsort1(v, left, last - 1, comp);
    qsort1(v, last + 1, right, comp);
}


int main(int argc, char *argv[]) 
{
    int nlines;
    for(int z=0;z<argc;z++)
    {	
        if(strcmp(argv[z], "-d") == 0) dic= 1;
        else if (strcmp(argv[z], "-r") == 0) rev=1;
        else if (strcmp(argv[z], "-f") == 0) fold=1;
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort1((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(strcmp1));
        
        if (rev==1)
        {
        	reverse((void **)lineptr);
        }
        writelines(lineptr, nlines);
    } else {
        printf("input too big to sort\n");
    }

    return 0;
}

