#include <iostream>
#include <string>
//--- Functions
//Functions need to be declared before they can be used in the code.
//A function can be declared initially in the program and defined later in the program.
//This will allow us to use the function in the program befrore we actually define it.


//By default all the arguments passed to the functions are passed by value, we can change it 
//to pass by reference by using '&'.
//Pass by value : Value is copied and the original will not change.
//Passed by reference.
//In java and most other programming language pass by refenrece is default, 
//but in C++ default is pass by value.

//--- Method/Function overloading is possible in C++.

using std::cout; using std::cin; using std::endl;

//--- Declare a function
double power(double, int);
//Above we only declare a function we diid not actually define it.
//We can define it any where in the program not

//We could define the function before it is called and not have to declare it separately.
//This is similar to variables, declaration and definition in one.
//Following is a void function.
void helloFunction(std::string message = "Hello World")//--- Default arguments.
{
    cout << message << endl;
}

//--- Function Templates
//template is a keyword, typename could also be class.
//Templatized function could be overloaded.
/*
    template <class type> ret-type func-name(parameter list) {
       // body of function
    } 
*/
template <typename T>
T add(T a, T b)
{
    return a + b;
}

int main(int argc, char const *argv[])
{
    cout << "Please enter a number and exponent : " << endl;
    double variable;
    int exponent;
    cin >> variable >> exponent;

    cout << "The resulting number is : " << power(variable, exponent) << endl; 

    helloFunction();

    int a = 10;
    int b = 12;
    
    std::cout << "The addition of the two number is : " << add(a, b) << endl; 

    return 0;
}

double power(double variable, int exponent)
{
    double result = 1;

    for (int i = 0; i < exponent; i++)
    {
        result *= variable;
    }

    return result;   
}

