#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXWORD 100

int linenum=1,ind=1;
struct linkedlistnode 
{
    int line_num;
    struct linkedlistnode *next;

};
struct tnode
{
    char *word;
    int count;
    struct linkedlistnode *line;
    struct tnode *left;
    struct tnode *right;
};
const char *noiseWords[] = {
    "a", "an", "and", "are", "at", "by", "but", "in", "is", "of", "on", "or", "the", "that", "this", "to", "with"
};

void printtree(struct tnode *root)
{
    if(root==NULL) return;
    printtree(root-> left);
    printf("%s - ", root->word);
    struct linkedlistnode * t=root->line;
    while(t!=NULL)
    {
        printf("%d ",t->line_num);
        t=t->next;
        
    }
    printf("\n");
    printtree(root-> right);
}
char *strdup1(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1); 
	if (p != NULL) strcpy(p, s);
	return p;
}
int getword(char *word, int lim)
{
    char c;
    while((c=getchar())!='\n' && c!=EOF && c!=' ' && c!=',' && c!='.' ) *(word++)=c;
    *word='\0';
    if(c=='\n') ind++;
    if(c==EOF) return EOF;
    return word[0];
}

int findkeyword(char *word) {
    int low = 0;
    int high = 16;

    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(word, noiseWords[mid]);

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
struct tnode *addtree(struct tnode *root, char *word,int ind)
{
    int k;
    if (root == NULL) {
        root = (struct tnode *)malloc(sizeof(struct tnode));
        root->count = 1;
        root->word = strdup1(word);
        root->line=(struct linkedlistnode *)malloc(sizeof(struct linkedlistnode));
        root->line->line_num=linenum;
        linenum=ind;
        root->line->next=NULL;
        root->left = NULL;
        root->right = NULL;
    } 
    else if ((k = strcmp(word, root->word)) == 0) 
    {
         struct linkedlistnode *temp;
         temp = root->line;
        while(temp->next != NULL && temp->line_num != linenum)
            temp = temp->next;
        if(temp->line_num != linenum)
        {
            temp->next = (struct linkedlistnode *)malloc(sizeof(struct linkedlistnode));
            temp->next->line_num = linenum;
            temp->next->next = NULL;
        }
    }  
    else if (k < 0) {
        root->left = addtree(root->left, word,ind);
    } else {
        root->right = addtree(root->right, word,ind);
    }
    return root;
}
int main()
{
    char word[MAXWORD];
    struct tnode *root;
    root = NULL;
    while(getword(word,MAXWORD)!=EOF && strcmp(word," ")!=0)
    {
        if(findkeyword(word)==-1) root = addtree(root,word,ind);
    }
    printtree(root);
}

