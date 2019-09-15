#include <iostream>
using namespace std;

struct D
{
	int date;
	int month;
	int year;
}input;

int n_days;

void add_year(D);
void add_month(D);
int check_leap(int);
void check_day(int, D);

int main()
{
	cout<<"Enter the date (DD): ";
	cin>>input.date;
	cout<<"Enter the Month (MM): ";
	cin>>input.month;
	cout<<"Enter the year (YYYY): ";
	cin>>input.year;
	
	add_year(input);
	add_month(input);
	n_days+=input.date;
	check_day(n_days, input);
	
	return 0;
}

void add_year(D temp)
{
	int a;
	a=temp.year-1;
	n_days=a*365;
	
	int j=n_days;
	
	//cout<<"n_days 1: "<<n_days<<endl; //
	
	int x=1;
	while(x<=a)
	{
		n_days+=check_leap(x);
		x++;
	}
	
	//cout<<"leap: "<<n_days-j<<endl;
	return;
}

int check_leap(int a)
{
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
	return x;
}

void add_month(D temp)
{
	for(int i=1; i<temp.month; i++)
	{
		switch(i)
		{
			case 1: n_days+=31;
					break;
			case 2: n_days+=28;
					n_days+=check_leap(temp.year);
					break;
			case 3: n_days+=31;
					break;
			case 4: n_days+=30;
					break;
			case 5: n_days+=31;
					break;
			case 6: n_days+=30;
					break;
			case 7: n_days+=31;
					break;
			case 8: n_days+=31;
					break;
			case 9: n_days+=30;
					break;
			case 10: n_days+=31;
					break;
			case 11: n_days+=30;
					break;
			case 12: n_days+=31;
					break;
		}
	}
	return;
}

void check_day(int a, D temp)
{
	//cout<<endl<<a<<endl;
	a=a%7;
	cout<<endl;

	cout<<"The Day on "<<temp.date<<"/"<<temp.month<<"/"<<temp.year<<" is: ";
	switch(a)
	{
		case 0: cout<<"Sunday";
				break;
		case 1: cout<<"Monday";
				break;
		case 2: cout<<"Tuesday";
				break;
		case 3: cout<<"Wednesday";
				break;
		case 4: cout<<"Thursday";
				break;
		case 5: cout<<"Friday";
				break;
		case 6: cout<<"Saturday";
				break;
	}
	return;
}
