#include <iostream>
using namespace std;

int main() 
{
    int i, n, factorial = 1;

    cout<<"Enter the Number to find it's Factorial ";
    cin>>n;
    if(n==0)
    factorial=1;
    else if(n<0)
    cout<<"Invalid! Number Must be Positive";
    else
    {
	for (i = 1; i <= n; ++i) 
        factorial *= i;  
    }
    cout<< "Factorial of "<<n<<" = "<<factorial;
    return 0;
}

