#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

#define HASHSIZE 101
#define MAXLINE 1000
struct nlist {          
    struct nlist *next; 
    char *name;         
    char *defn;         
};


static struct nlist *hashtab[HASHSIZE]; 

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % HASHSIZE;
}


struct nlist *lookup(char *s) {
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; 
    return NULL;       
}

void undef(char *s) 
{
    struct nlist *temp;
    if ((temp = lookup(s)) == NULL) 
        return ;
    else {
        if (temp->next == NULL) 
        {
            hashtab[hash(s)] = NULL;
            free((void *) temp);
        } 
        else 
        {
            temp->next = temp->next->next;
            temp = temp->next;
        }
    }
    return ;
}

char *strdup1(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1); 
	if (p != NULL) strcpy(p, s);
	return p;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { 
        np = (struct nlist *) malloc(sizeof(*np));

        if (np == NULL || (np->name = strdup1(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else                      
        free((void *) np->defn); 

    if ((np->defn = strdup1(defn)) == NULL)
        return NULL;

    return np;
}
char mgetline(char *word)
{
	char c;
	while(isspace(c=getchar()));
	*word++=c;
	while((c=getchar())!='\n' && c!=EOF)
	{
		*word++=c;
	}
	if (c==EOF)return EOF;
	*word='\0';
	return word[0];
}


int main() 
{
	char line[MAXLINE];
	char *keys[1000];
	int number_keys=0;
    while(mgetline(line)!=EOF)
    {
    	char word[MAXLINE];
    	char key[MAXLINE];
    	char value[MAXLINE];
    	int i;
    	for(i=0;i<7;i++)
    		word[i]=line[i];
    	word[i]='\0';
    	if(strcmp(word,"#define")==0)
    	{
    		//printf("%s" ,word);
    		char c=line[i];
    		while((c=line[i])==' ') i++;
    		int j=0;
    		while( (c=line[i])!=' ') {i++;key[j++]=c;}
    		key[j]='\0';
    		while((c=line[i])==' ') i++;
    		j=0;
    		while( (c=line[i])!='\n') {i++;value[j++]=c;}
    		value[j]='\0';
    		install(key,value);
    		keys[number_keys] = strdup1(key);
    		number_keys++;
    	}
    }

    struct nlist *result;


    for (int i = 0; i < number_keys; i++) 
    {
        if ((result = lookup(keys[i])) == NULL)
         {
            printf("key was not found\n");
        }
         else 
         {
            printf("name : %s - defination : %s\n", result->name, result->defn);
        }
    }
    return 0;
}


