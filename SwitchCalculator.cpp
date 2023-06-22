#include <iostream>
#include <conio.h>
using namespace std;
int main()
{
	char operation;
	int num1, num2;
	cout<<"Input first number\n";
	cin>> num1;
	cout<<"input second number\n";
	cin>> num2;
	cout<<"input operation\n";
	cin>> operation;
	switch(operation)
	{
		case '+':
		cout<<"Addition\n\n";
		cout<<num1<<" + "<<num2<<" = "<<num1+num2;
		break;
		case '-':
		cout<<"Subtraction\n\n";
		cout<<num1<<" - "<<num2<<" = "<<num1+num2;
		break;
		case '*':
		cout<<"Multiplication\n\n";
		cout<<num1<<" * "<<num2<<" = "<<num1+num2;
		break;
		case '/':
		cout<<"division\n\n";
		cout<<num1<<" / "<<num2<<" = "<<num1+num2;
		break;
		case '%':
		cout<<"Modulus\n\n";
		cout<<num1<<" % "<<num2<<" = "<<num1+num2;
		break;
		default:
			cout<<"invalid";
			break;
		}
	getch();
	return 0;
}
		


//EDP5L (8:00-10:00am)
//This program will find the factorial of a given number
//programmed by: Petina, Alvin B.
//Instructor: Rodrigo S. Pangantihon Jr.


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
