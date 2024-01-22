#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXWORD 1000

struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};
char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int findkeyword(char *word) {
    int low = 0;
    int high = 31;

    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(word, keywords[mid]);

        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}
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
char *strdup1(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1); 
	if (p != NULL) strcpy(p, s);
	return p;
}
void ungetch(char c)
{
    ch = c;
    unget = 1;
}

int getword(char *word, int lim)
{
    int com = 0;
    int c;
    char *w = word;

    while (isspace(c = getch()));

    if (c != EOF)
    {
        *w++ = c;
    }
    if (!isalpha(c)) {
    	if(c==EOF) return c;
        if (c == '#')
            while ((c = getchar()) != '\n');
        if (c=='"') while ((c = getchar()) != '"');
        else if (c == '/') {
            c = getchar();
            if (c == '/') {
                while ((c = getchar()) != '\n');
            } else if (c == '*') {
                while (com != 2) {
                    c = getchar();
                    if (c == '*') {
                        com++;
                        c = getchar();
                        if (c == '/')
                            com++;
                        else
                            com = 0;
                    }
                }
            }
        }
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
        if(*w=='_') continue;
            ungetch(*w);
            break;
        }
    }
    
    *w = '\0';
    return word[0];
}

struct tnode *addtree(struct tnode *root, char *word)
{
    int k;
    if (root == NULL) {
        root = (struct tnode *)malloc(sizeof(struct tnode));
        root->count = 1;
        root->word = strdup1(word);
        root->left = NULL;
        root->right = NULL;
    } else if ((k = strcmp(word, root->word)) == 0) {
        root->count += 1;
    } else if (k < 0) {
        root->left = addtree(root->left, word);
    } else {
        root->right = addtree(root->right, word);
    }
    return root;
}

void treeprint(struct tnode *root)
{
    if (root == NULL)
        return;
    treeprint(root->left);
    if(findkeyword(root->word)==-1) printf("%s %d\n", root->word, root->count);
    treeprint(root->right);
}

int main()
{
    char word[MAXWORD];
    struct tnode *root;
    root = NULL;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]))
            root = addtree(root, word);
    }

    treeprint(root);
    return 0;
}

