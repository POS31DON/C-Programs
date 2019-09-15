#include<iostream>

using namespace std;

int fact(int n)
{
	//Base case
	if (n==0){
		return 1;
	}
	int ans_part = fact(n-1);
	int ans_full = n*ans_part;
	
	return ans_full;
}


int main()
{
	int n;
	cin>>n;
	
	cout<<fact(n)<<endl;
	
	return 0;	
}
