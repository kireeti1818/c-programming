#include<stdio.h>
#include <string.h>

const char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
const char months[12][12] = 
    {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"}
;

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
    int i;
    for(i=0;day>=daytab[leap][i];i++)
    {
        day=day-daytab[leap][i];
    }
    //printf("%d %d \n",day,i);
    *pres_day=day;
    *pres_month=i;
 }
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
    int i;
    for(i=0;i<month;i++)
    {
        day+=daytab[leap][i];
    }
    return day;
 }
 int main()
 {
     int month,day;
     month_day(2024,70,&month,&day);
     if (month==-1 || day==-1)
     {
     	printf("wrong input\n");
     } 
     else
     {
    	printf("%s %d \n",months[month-1],day);
    }
    char mon[12]="march";
    for(int i=0;i<12;i++)
    {
        if (strcmp(months[i], mon) == 0) {
        int x=year_day(2024,i+1,32);
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
    
    return 0;
    
 }
