#include<stdio.h>
#include<stdlib.h>

int main()
{
    int line = 0, page = 1, pr = 0;
    FILE *fp;

    
    fp = fopen("pqr.txt", "r"); // Open the file for reading
	
    if (fp == NULL)  // Check if the file opened successfully
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char c;

    
    while ((c = fgetc(fp)) != EOF) // Loop through each character in the file
    {
        
        if (line == 0 && pr == 0) // Check if it's the start of a new page
        {
            printf("\n---START OF PAGE %d---\n\n", page);
            pr = 1;
        }

       
        if (c == '\n')  // if the character is a newline character increment line
            line++;
        putchar(c);

        
        if (line == 5) // Check if we have reached the end of a page
        {
            printf("\n---END OF PAGE %d---\n", page);
            line = 0; // Reset line count and page flag
            pr = 0;
            page++;
        }
    }

    fclose(fp);

    return 0;
}
