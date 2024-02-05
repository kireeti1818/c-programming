#include <stdio.h>
#include <stdlib.h>

#define MAXBYTES (unsigned)10240
#define NALLOC 1024

typedef long Align;

union header 
{
    struct 
    {
        union header *ptr; 
        unsigned size;    
    } s;
};

typedef union header Header;

static unsigned maxalloc;    
static Header base;         
static Header *freep = NULL; 

static Header *morecore(unsigned nu) {
    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) /* no space at all */
        return NULL;

    up = (Header *) cp;
    up->s.size = nu;

    // Do not free the memory immediately, return the pointer instead
    return up;
}


void *mymalloc(unsigned nbytes) 
{
    Header *p, *prevp;
    
    unsigned nunits;

    if (nbytes > MAXBYTES)
    {
        printf("can't allocate memory\n");
        return NULL;
    }
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) 
    {
        if (p->s.size >= nunits) 
        {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else 
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *) (p + 1);
        }

        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}


void free(void *ap)
{
    Header *bp, *p;
    bp = (Header *) ap - 1;
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; 

    if (bp + bp->s.size == p->s.ptr) 
    { 
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } 
    else
        bp->s.ptr = p->s.ptr;

    if (p + p->s.size == bp) 
    { 
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } 
    else
        p->s.ptr = bp;
    freep = p;
}

int main(int argc, char *argv[]) 
{
    int *p = NULL;
    int i = 0;
    p = mymalloc(100);
    if (NULL == p)
     {
        printf("can't allocate memory\n");
    } 
    else 
    {
        for (i = 0; i <= 100; i++) 
        {
            printf("%x", p[i]);
            if (i % 8 == 7) 
            {
                printf("\n");
            }
        }
        printf("\n");
        free(p);
    }
    return 0;
}