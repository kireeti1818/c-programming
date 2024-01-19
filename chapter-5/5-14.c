#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000

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

int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
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

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0,rev=0;

    if (argc > 1)
    {	
        if(strcmp(argv[1], "-n") == 0) numeric = 1;
        else if (strcmp(argv[1], "-r") == 0) rev=1;
    }
    if (argc == 3 && strcmp(argv[2], "-r") == 0) rev= 1;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort1((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))(numeric ? (int (*)(void *, void *))numcmp : (int (*)(void *, void *))strcmp));
        
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

