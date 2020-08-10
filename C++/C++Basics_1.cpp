#include <iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#include<limits>

//We use the name space so that we can use functions from the std library direcltyu without referencing
//std everytime.
using namespace std;
//We could also we and is prefered to use 
// using std::cout

//main function is called automatically by when the function is executed.
//So it can be thought as the entry point into the program.
//main function should always return an int.
int main()
{

    //--- Print to screen. We use cout -> Console Out
    cout << "Hello world!" << endl;

    //--- Declare a variable
    int i = 10;
    cout << "The count is : " << i << endl << "Second Line" << endl;


    //--- Take user input from console.
    //THis could be a string but we are using the varaible above to store it,
    //so it is parsed to integer automatically.
    cout << "Please enter a number to store in i : ";
    cin >> i;
    //clears the data in the stream.
    cin.clear(); 
    //We have to use the ignore method of the cin so that the all the data in the stream
    //clears and when we use the next cin or getline() the value is reset and we can enter
    //a new number.
    //cin.ignore(numberOfCharactersToIgnore, ignoreTillReachCharacter);
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "You entered : " << i << endl;

    //--- Using a function in the cmath library.
    cout << "Square of the number you entered is : " << pow(i , 2) << endl;
    cout << "Square Root of the number entered is : " << sqrt(i) << endl;
    //There Are other useful methods that can be used with the cmath libriary.
    //floor(),  ceil(), trunc(), round(), fmax(), fmin(), remainder() etc are some of the most used. 

    //--- Data types in C++
    //Integer values signed and unsigned.
    short a;
    int b;
    long c;
    long long d;

    unsigned short e;
    unsigned int f;
    unsigned long g;
    unsigned long long h;

    //To get the size of datatypes in bytes(8bits = 1byte) we use.
    int bytes_in_int = sizeof(int);
    cout << bytes_in_int  << " Is the number of bytes alloted to int. That is " << bytes_in_int*8 << " bits." << endl;

    //char datatype
    char initialA = 'a';
    cout << "Character 'a' as number is " << (int) initialA << endl;
    //Above we use casting to convert a character into an int.
    //The conversion from a character toa number is based on the ASC-II table.

    //bool datatype
    bool is_someone_there = true;
    //Any value other than 0 and false is interpreted as one.
    //It is similar to javascript in this case.

    //boolean in C++ is always printed as 1 and 0.
    //If we want to print true or false we use the boolalpha from std.
    cout << "This is a boolean value : " << boolalpha << is_someone_there << endl;

    //Floating point datatype
    float j;
    double k = 7.7E4; //This will evaluate to 7.7 * 10^4
    long double l;

    //--- Constants
    const double PI = 3.141576;
    cout << "The constant value of pi is : " << PI << endl;

    //There are other types of constants called as enum constants
    enum { y = 50 , z = 3 };    
    cout << "The constant value from enum are  : " << y << " and " << z << endl;

    //--- Strings : C strings and String Class.
    //string Class is the part of std library.
    string hello_name = "Hello Name";
    cout << "The message in the string is : " << hello_name << " Of length : " << hello_name.length() << endl;

    //C  style string : In C the strings are just an array of characters.
    //C style string are immutable.
    char string_array[] = "This is a C style String : Array of characters";
    cout << string_array << endl;

    //To get string from user input we use getline(cin, string_varible).
    //This is because the cin by itself stores the value until a white space and not complete line. 
    cout << "Please enter your full name : ";
    string name;
    getline(cin, name);
    cout << "Your name is : " << name << endl;

    //String Functions
    //length() -> same as -> size(), append(), insert(index, "value"),
    //erase(), replace(index, howManyChar, "value")
    //find("value"), substr(start, howLong), compare("compareToValue") -> gives 1 or 0

    //--- Ternary if statement
    int num1 = 10;
    int num2 = 20;


    cout << "Compare Numbers : ";
    num1 == num2 ? cout << "Numbers are the same." << endl : cout << "Numbers are different." << endl;

    //--- Random number generator
    //The rand function gives a random number that could any int.
    //We could use rand() % number to get a number between zero and that number to get
    //random number in a given range.
    std::cout << rand() << std::endl; 

    return 0;
}

//namespaces : While using name space we have to add the name space to
//both the header file as well as implementation.

//We could use name space by using

namespace utils{

    //And then we add all the code that needs to belong to the namespace inside this.
    //We can use a namespace code after it is defined similar to the functions.

}

//Check Functions_2.