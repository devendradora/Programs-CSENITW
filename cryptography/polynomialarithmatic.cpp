#include <stdio.h>
#include <iostream>

using namespace std;

int mod(int a , int b)
{
	int result = a % b;
	
	if(result < 0)
	{
		result += b;
	}

    return result;
}

void add(int* sum , int* a , int* b , int p , int n)
{
    for(int i=0 ; i<n ; i++)
    {
    	sum[i] = mod( (a[i] + b[i]) , p );
    }
}


void substract(int* diff , int* a , int* b , int p , int n)
{
    for(int i=0 ; i<n ; i++)
    {
    	diff[i] = mod( (a[i] - b[i]) , p );
    }
}


int main()
{
    int p , n ;

    cout << "Enter p : ";
    cin >> p;

    cout << "Enter n : ";
    cin >> n;

    int a[n];
    int b[n];

    cout << "Enter polynomial a - \n";

    for(int i = 0 ; i < n ; i++)
    {
    	cout << "x^" << i << " = ";
    	cin >> a[i]; 
    }


    cout << "\nEnter polynomial b - \n";

    for(int i = 0 ; i < n ; i++)
    {
    	cout << "x^" << i << " = ";
    	cin >> b[i]; 
    }

    int sum[n];

    add(sum , a , b , p , n);

    cout << "\nSum of a and b is - \n";

    for(int i = 0 ; i < n ; i++)
    {
    	cout << "x^" << i << " = " << sum[i] << "\n";
    }
    cout << "\n";

    int diff[n];

    substract(diff , a , b , p , n);

    cout << "\nDifference of a and b is - \n";

    for(int i = 0 ; i < n ; i++)
    {
    	cout << "x^" << i << " = " << diff[i] << "\n";
    }
    cout << "\n";

    int qoutient[n];
    int remainder[n];
}