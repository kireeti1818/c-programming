#include<stdio.h>
#include<string.h>
char months[12][12] = 
    {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};
char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
int year_day(int year,int month, int day)
{
	if (day<0)
	{
    		return -1;
    	}
    int leap = (year%4==0 && year%100!=0) || year%400==0;
    if (daytab[leap][month]<day)
    {
    	return -1;
    }
    char *month_days=daytab[leap];
    while(month--)
    {
    	day=day+ *month_days++;
    }
    return day;
 }
 void month_day(int year, int day, int *pres_month, int *pres_day)
{
	if (day<0)
	{
		*pres_day=-1;
    		*pres_month=-1;
    		return;
    	}
    int leap = (year%4==0 && year%100!=0) || year%400==0;
    if (leap==1)
    {
    	if (day>366)
    	{
    		*pres_day=-1;
    		*pres_month=-1;
    		return;
    	}
    }
    else
    {
    	if (day>365)
    	{
    		*pres_day=-1;
    		*pres_month=-1;
    		return;
    	}
    }
    char *month_days=daytab[leap];
    while(day>*month_days)
    {
    	day-=*month_days++;
    }
     *pres_month= month_days - daytab[leap];
    *pres_day=day;
}
int main()
{

    char mon[12]="july";
    for(int i=0;i<12;i++)
    {
        if (strcmp(months[i], mon) == 0) {
        int x=year_day(2024,i+1,26);
            if (x==-1)
            {
            	printf("wrong input\n");
            }
            else
            {
            	printf("%d \n",x);
            }
            break;
        }
    }
    int month,day;
     month_day(2024,208,&month,&day);
     if (month==-1 || day==-1)
     {
     	printf("wrong input\n");
     } 
     else
     {
    	printf("%s %d \n",months[month-1],day);
    }
}
