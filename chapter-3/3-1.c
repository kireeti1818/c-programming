#include<stdio.h>
int main()
{
	int n=8;
	int a[]={1,2,3,4,5,6,7,8};
	int search = 4;
	int low=0;
	int high = n-1;
	int mid=(low+high)/2;
	while(low<=high && search!=a[mid])
	{
		if (search >a[mid])
		{
			low=mid+1;
		}
		else
		{
			high=mid-1;
		}
		mid=(low+high)/2;
	}
	if(search==a[mid])
	{
		printf("%d",mid);
	}
	else
	{
		printf("-1");
	}

}
