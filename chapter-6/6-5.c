#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

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


int main() {
    struct nlist *hashtable[6] = {
            (install("abc", "ABCD")), 
            (install("def", "DEF")), 
            (install("xyz", "XYZ")),
            (install("pqr", "PQR")), 
            (install("ghi", "GHI")), 
            (install("rst", "RST"))};

    int i;
    for (i = 0; i < 6; i++) {
        printf("name : %s - defination : %s\n", hashtable[i]->name, hashtable[i]->defn);
    }

    undef("rst");
    undef("xyz");

    struct nlist *result;

    char *keys[6] = {"xyz", "def", "abc", "pqr","ghi","rst"};

    for (i = 0; i < 6; i++) {
        if ((result = lookup(keys[i])) == NULL) {
            printf("key was not found\n");
        } else {
            printf("name : %s - defination : %s\n", result->name, result->defn);
        }
    }

    return 0;
}

