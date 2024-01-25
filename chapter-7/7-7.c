#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000


void searchPattern(FILE *fp, const char *pattern, const char *filename)  // Function to search for a pattern in a file and print matching lines
{ 
    char line[MAXLINE];
    int line_number = 0;

    while (fgets(line, MAXLINE, fp) != NULL) 
    {
        line_number++;
        if (strstr(line, pattern) != NULL) // Check if the pattern is present in the current line
        {
            printf("Found in file: %s\nLine number: %d\nLine: %s\n", filename, line_number, line);
        }
    }
}

int main(int argc, char *argv[]) 
{
    
    if (argc < 2) 
    {
        printf("Neither filename nor pattern was given.\n");
        return 0;
    }

    const char *pattern = argv[1];     // Get the pattern from the command line arguments


    if (argc == 2)     // Check if only the pattern is provided , the search in input
    {
   
        searchPattern(stdin, pattern, "stdin");
    } 
    else 
    {
        for (int i = 2; i < argc; i++)         // Iterate through the provided file names
        {
            FILE *fp = fopen(argv[i], "r");             // Open the current file for reading
            if (fp == NULL) 
            {
                fprintf(stderr, "Cannot open file: %s\n", argv[i]);
                continue;
            }
            searchPattern(fp, pattern, argv[i]); // call the search function to find the pattern in the file
            fclose(fp);
        }
    }

    return 0;
}
