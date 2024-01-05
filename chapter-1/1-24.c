#include<stdio.h>
int brace=0,para=0,brackets=0,single_quote=0,double_quote=0,state=0,count=0;
char c;
int main()
{
	while((c=getchar())!=EOF)
	{
		if (c=='/') 
		{
			if (count==0) count++;
			else if (count==1){ count++;
			state=1;
			}
		}
		else
		{
			if(c=='\n')
			{
				state=0;
				count=0;
			}
			if (count==2)
			{
				continue;
			}
			else
			{
				state=0;
				count=0;
			}
		}


		if (state==0)
		{

			if (c=='"')
			{	if (double_quote==1)double_quote++;
				else double_quote--;
			}
			else if (c=='\'')
			{
				if (single_quote==1)single_quote++;
				else single_quote--;
			}
			if (c=='[')
			{
				if (single_quote==1 || double_quote==1) continue;
				else
				brackets++;
			}
			else if (c==']')
			{
				if (single_quote==1 || double_quote==1) continue;
				else
				brackets--;
			}
			else if (c=='(')
			{
				if (single_quote==1 || double_quote==1) continue;
				else		
				brace++;
			}
			else if (c==')')
			{
				if (single_quote==1 || double_quote==1) continue;
				else
				brace--;
			}
			else if (c=='{')
			{
				if (single_quote==1 || double_quote==1) continue;
				else
				para++;
			}
			else if (c=='}')
			{
				if (single_quote==1 || double_quote==1) continue;
				else		
				para--;
			}
		}	
	}
	if (brace!=0)
	{
		printf("braces are missing in the code\n");
	}
	if (para!=0)
	{
		printf("parentheses are missing in the code\n");
	}
	if (brackets!=0)
	{
		printf("Brackets are missing in the code\n");
	}
	if (single_quote!=0)
	{
		printf("single quote are missing in the code\n");
	}
	if (double_quote!=0)
	{
		printf("double quote are missing in the code\n");
	}
	return 0;
	
}

