#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXWORD 100


struct tnode // structure which stores both word and count of word
{
    char *word;
    int count;
};


struct tnode array[MAXWORD];
int length=0;


int findelement(char *word,int i) /* used to find the word is present in the structure or not. if present we will increment count by 1, other wise we will add word and make count as one to the array*/
{
    int low = 0;
    int high = i;

    while (low < high) {
        int cmp = strcmp(word, array[low].word);

        if (cmp == 0) 
            return low;
        low++;
    }
    return -1;
}


int partition(struct tnode *arr,int low,int high) // use in quick sort
{   
  int pivot=arr[high].count;
  int i=(low-1);
   
  for(int j=low;j<=high;j++)
  {
    if(arr[j].count<pivot)
    {
      i++;
      struct tnode temp =arr[i];
      arr[i]=arr[j];
      arr[j]=temp;

    }
  }
  
  struct tnode temp =arr[i+1];
  arr[i+1]=arr[high];
  arr[high]=temp;
  return (i+1);
}
      
void quickSort(struct tnode *arr,int low,int high) // quick sort, it sort array by frequency
{
 
  if(low<high)
  {
    int pi=partition(arr,low,high);
    quickSort(arr,low,pi-1);
    quickSort(arr,pi+1,high);
  }
}


void swap(struct tnode  *v, int i, int j) {
    struct tnode  temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


void lexico(struct tnode *v, int left, int right) // after sorting the structure by frequency, we are storting the array by aplhabatical order of the words
{
    int i, last;

    if (left >= right) return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i].word, v[left].word) < 0)
            swap(v, ++last, i);

    swap(v, left, last);
    lexico(v, left, last - 1);
    lexico(v, last + 1, right);
} 


int getword(char *word, int lim) // used to get the words from the line 
{
    char c;
    while((c=getchar())!='\n' && ((c>=65 && c<=90) || (c>=97 && c<=122))) *(word++)=c;
    *word='\0';
    if(c==EOF) return EOF;
    return word[0];
}


char *strdup1(char *s) // used to create a space , copies the content of word to p and returns pointer of the array.
{
    char *p;
    p = (char *) malloc(strlen(s)+1); 
    if (p != NULL) strcpy(p, s);
    return p;
}


void sortarray() // here we will call the both sort and lexicograpgical sort of the word
{
    quickSort(array,0,length);

    int i=1;
    int coun=array[1].count;
    int lim=1;
    while(i<length+1)
    {
        //printf("%d ",array[i].count);
        if(array[i].count!=coun)
        {
            if(lim!=i-1)
            lexico(array,lim,i-1);
            coun=array[i].count;
            lim=i;
        }
        i++;
    }
    if(lim!=i-1) lexico(array,lim,i-1);
}


int main()
{
    char word[MAXWORD];
    int word_len;
    int found=0;
    while(getword(word,MAXWORD)!=EOF)
    {
        
        if((word_len=strlen(word))!=0)
        {
            for (int i = 0; i < word_len; i++) word[i] = tolower(word[i]);
            if (length!=0)
            {
                found=findelement(word,length);
                if (found==-1)
                {
                    array[length].word = strdup1(word);
                    array[length].count=1;
                    length++;
                }
                else
                {
                    array[found].count+=1;
                }
                //printf("%d\n",found);
            }
            
            else
            {
                array[length].word = strdup1(word);
                array[length].count=1;
                length++;
                //printf("%s %d\n",word,i);
            }
        }
        
    }
    if((word_len=strlen(word))!=0)
    {
        for (int i = 0; i < word_len; i++) word[i] = tolower(word[i]);
        if (length!=0)
        {
            found=findelement(word,length);
            if (found==-1)
            {
                array[length].word = strdup1(word);
                array[length].count=1;
                length++;
            }
            else
            {
                array[found].count+=1;
            }
            //printf("%d\n",found);
        }
        
        else
        {
            array[length].word = strdup1(word);
            array[length].count=1;
            length++;
            //printf("%s %d\n",word,i);
        }
    }
    sortarray();
    for(int j=1;j<=length;j++)
    {
        printf("\n%d %s",array[j].count,array[j].word);
    }
    printf("\n");
}
