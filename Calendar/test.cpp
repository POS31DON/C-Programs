#include <iostream>
using namespace std;

int main()
{
	int a;
	cin>>a;
	int x=0;
	if(a%4==0)
	{
		if(a%100==0)
		{
			if(a%400==0)
			{
				x=1;
			}
			else
			{
				x=0;
			}
		}
		else
		{
			x=1;
		}
	}
	else
	{
		x=0;
	}
	
	cout<<x;
	return x;
}
