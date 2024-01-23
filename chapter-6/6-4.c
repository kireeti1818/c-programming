#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXWORD 100
struct tnode
{
    char *word;
    int count;
};
struct tnode array[MAXWORD];
int length=0;
int findelement(char *word,int i)
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
int partition(struct tnode *arr,int low,int high)
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
            
void quickSort(struct tnode *arr,int low,int high)
{
 
  if(low<high)
  {
    int pi=partition(arr,low,high);
    quickSort(arr,low,pi-1);
    quickSort(arr,pi+1,high);
  }
}
int getword(char *word, int lim)
{
    char c;
    while((c=getchar())!='\n' && ((c>=65 && c<=90) || (c>=97 && c<=122))) *(word++)=c;
    *word='\0';
    if(c==EOF) return EOF;
    return word[0];
}
char *strdup1(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1); 
	if (p != NULL) strcpy(p, s);
	return p;
}

int main()
{
    char word[MAXWORD];

    
    int found=0;
    while(getword(word,MAXWORD)!=EOF && word!=NULL)
    {
    	
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
    quickSort(array,0,length);
    for(int j=1;j<=length;j++)
    {
    	printf("\n%d %s",array[j].count,array[j].word);
    }
    printf("\n");
}
