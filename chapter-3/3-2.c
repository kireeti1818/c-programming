#include<stdio.h>
#define MAX_LEN 1000
void escape(char[],char[]);
void escape1(char[],char[]);
int main()
{
	char s[MAX_LEN],t[MAX_LEN],u[MAX_LEN],c;
	int i=0;
	while((c=getchar())!=EOF)
	{
		s[i++]=c;
	}
	s[i]='\0';
	//printf("%s",s);
	escape(s,t);
	printf("\n%s\n",t);
	escape1(t,u);
	printf("%s\n",u);
}
void escape(char s[],char t[])
{
	
	int i=0,j=0;
	while(s[i]!='\0')
	{	
		char c=s[i];
		switch (c)
		{
			case ('\n'):
				t[j++]='\\';
                        	t[j++]='n';
                        	i++;
				break;
			case('\t'):
				t[j++]='\\';
                                t[j++]='t';
                                i++;
                                break;
			default:
				t[j++]=s[i++];
				break;


		}

	}
	t[j]='\0';
	
}
void escape1(char s[],char t[])
{
	int i=0,j=0;
        while(s[i]!='\0')
        {       
                switch(s[i])
		{
			case('\\'):
				switch(s[++i])
				{
					case('n'):
						t[j++]='\n';
						break;
					case('t'):
						t[j++]='\t';
						break;
					default:
						t[j++]='\\';
						i--;
						break;
				}
			default:
				t[j++]=s[i++];
		}
	}
	t[j]='\0';

}
