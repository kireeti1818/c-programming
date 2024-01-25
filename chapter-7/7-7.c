#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void searchpattern(FILE *fp, const char *pattern, const char *filename) 
{
    char line[MAXLINE];
    int line_number = 0;
    while (fgets(line, MAXLINE, fp) != NULL) 
    {
        line_number++;

        if (strstr(line, pattern) != NULL)
        {
            printf("Found in file :- %s \nLine number :- %d\nLine :- %s\n", filename,line_number ,line);
        }
    }
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("neither filename nor pattern was given\n");
        return 0;
    }
    const char *pattern = argv[1];
    if (argc == 2) 
    {
        searchpattern(stdin, pattern, "stdin");
    } 
    else 
    {
        for (int i = 2; i < argc; i++) 
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) 
            {
                fprintf(stderr, "Cannot open file: %s\n", argv[i]);
                continue;
            }

            searchpattern(fp, pattern, argv[i]);
            fclose(fp);
        }
    }

    return 0;
}
