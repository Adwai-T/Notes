#include <iostream>
#include <string>
#include <limits>
#include <vector>
//String Stream Library
#include <sstream>
#include <numeric>
#include <cmath>
//For Threads
#include <thread>
//Time Libraries
#include <chrono>
#include <mutex>
#include <ctime>
//For Function As Argument To other Function.
#include <functional>
//Memory Allotment
#include <memory>
#include <stdio.h>
#include <iomanip> // for std::setprecision()
#include <bitset>//for bitwise manipulations

using namespace std;

void executeThread(int id)
{
    auto nowTime = chrono::system_clock::now();
    time_t sleepTime = chrono::system_clock::to_time_t(nowTime);
    tm myLocalTime = *localtime(&sleepTime);
    cout << "Thread" << id << "Sleep Time" << ctime(&sleepTime) << endl;

    //myLocalTime have varaibles like myLocalTime.tm_mon, tm_mday
    //tm_year, tm_hour, tm_min, tm_sec

    this_thread::sleep_for(chrono::seconds(3));

    nowTime = chrono::system_clock::now();
    sleepTime = chrono::system_clock::to_time_t(nowTime);

    cout << "Thread" << id << " Awake Time " << ctime(&sleepTime) << endl;
}

//Passing Function to Another Function.
double addTwoNumbers(double num1, double num2)
{
    return num1 + num2;
}

double addThreeNumbers(function<double(double,double)> func, double num3)
{
    return func(1, 2) + num3;
}

//--- Enum Defination
enum Color
{
    COLOR_BLACK, //will hold value 0 when called.
    COLOR_WHITE, //will hold value 1 and so on further in the enum.
    COLOR_RED,
    COLOR_BLUE
};
//Having same values for enum elements is possible but not recommended.

//Static variables
int incrementAndReturnNumber()
{
    static int i = 0;
    return ++i;
}

int main()
{
    cout << "Start" << endl;

    //--- Fixed Width integers
    //For cross platfrom protability c99 introduced fixed width integers.
    std::int32_t number_32bit= 1254;
    //Similarly we can have unit32_t which is unsigned int.
    //Other fixed width ints are : int8_t, int16_t, int64_t and their respective unsigned values.
    //Downside : The above fixed-width integers should be avoided, as they may not be defined on all target architectures.

    //--- Fast and least integers
    std::int_fast32_t number_32bit_fast = 1268;
    //Similar for 8, 16, 32, 64 and also can similarly have int_least32_t. 
    //Similarly there are unsigned types that can be defined as uint_fast#_t.
    //Use least for memory conservation and fast for performace
    //8 bit int in both above cases might behave as char in some systems.

    //--- sizeof() and size_t
    //std::size_t is defined as an unsigned integral type, and it is typically
    //used to represent the size or length of objects.
    cout <<"sizeof(size_t) : " << sizeof(size_t) << endl;

    //---Precision in floating point numbers
    double num_double = 0.1; //if number is defined with f like 12.2f it is default to double when passed or assigned.
    cout << setprecision(17) << "\n Number double with 17 precision set : " << num_double << endl;

    //Increment and decrement operators
    //Prefix ++x operator are prefered for performance as they : Increment x, then return x,
    //where as x++ operator : Copy x, then increment x, then return the copy
    int inc_x{2};
    int inc_y = ++inc_x; //value inc_y is 3
    inc_x = 2;
    int inc_z = inc_x++; //value inc_z is 2
    cout << "Increment opertaor Prefix : inc_y = : " << inc_y << endl;
    cout << "Increment opertaor Postfix : ++inc when inc =  : " << inc_z << endl;
    //Similar for --
    //It is not recommended to pass x as well as x++ or ++x to a function as the value will
    //depend on what order the compiler executes it.

    //--- Character Functions
    char letterZ = 'z';
    char char5 = '5';
    cout << "Is z a letter or number : " << isalnum(letterZ) <<endl;
    //isalpha() isdigit() isspace();

    //--- inline consts
    // inline constexpr double PI { 3.1415 }; //inline varaibles cannot be defined inside of a function
    constexpr double PI = 3.1415;
    cout << "Value of constant pi : " << PI << endl;
    //After C++17 we can define inline constants.
    //The inline constant have external linkages by default.

    //--- Static local variables
    //The variable will remain in memory till the end of the program,
    //unlike normal variables that are destroied when they go out of scope.
    cout << "First call to function with static variable i : " << incrementAndReturnNumber() << endl;
    cout << "Second call to function with static variable i : " << incrementAndReturnNumber() << endl;
    cout << "Third call to function with static variable i : " << incrementAndReturnNumber() << endl;

    //--- typedef and type alias
    typedef int integer_number;
    integer_number int_num1 = 10;//intger_number is just as if using `int int_num1 = 10`, that is as an alias.
    cout << "Value of type integer_number : " << int_num1 << endl;

    using distance = int;
    distance distance_num1 = 12;
    cout << "Value of type distance : " << distance_num1 << endl;

    //--- Casting
    //C type casting
    int cast_i1{1};
    float cast_f1{(float)cast_i1/2};
    //C++ type casting
    double cast_d1{double(cast_i1)/2};
    cout << "Casting result of divide by 2 respectively of C style and C++ style : " << cast_f1 << "\t" << cast_d1 << endl;
    //static_cast
    float static_cast_f1{ static_cast<float>(cast_i1)/2 };
    cout << "Result of divide by 2 from static cast : " <<  static_cast_f1 << endl;
    //From above all three static cast should be prefered.

    //--- Pointers 
    int number_value = 10;
    int *number_pointer = &number_value;//Best practice to put the * at the start variable name;
    cout << "Number pointer value : " << number_pointer << endl;
    cout << "Value of number from Pointer : " << *number_pointer << endl;
    cout << "Type of value at pointer location returned by typeid(&variableName)::name() : " 
         << typeid(number_pointer).name() << endl;
    //Null Pointers
    float *ptr_float { 0 };  // ptr is now a null pointer
    //Starting from c++ 11 we can use nullptr to instanciate pointer that is null
    int *ptr_int { nullptr }; // note: ptr is still an integer pointer, just set to a null value
    //While a pointer is returned by a function we put the * at the end of return type int* fun() as Best practice

    //--- Dynamically assign memory
    int *pointer_intValue{ new int{ 6 } }; // dynamically allocate an integer
    //The above is uniform initialziation, it can also be directly initialized by using = or by new int (6).
    int *otherPointer_intValue{ pointer_intValue }; // otherPtr is now pointed at that same memory location
    cout << "Pointer Address : " << pointer_intValue << "\t Stores Value : " << *pointer_intValue << endl;
    delete pointer_intValue; // return the memory to the operating system.  ptr and otherPtr are now dangling pointers.
    //Once pointer_intValue is deleted the pointer address points to no value and is called dangling pointer.
    //After deleting the pointer should be set to nullptr.
    pointer_intValue = nullptr; // ptr is now a nullptr
    otherPointer_intValue = nullptr;

    //Using Enum values defined above
    //Enum values are defined in the same scope as the enum definition.
    //As we have defined our enum in the global scope of this file we can direclty get the value.
    Color paint{ COLOR_BLACK };
    Color house = COLOR_BLUE;
    cout << "Color of the house from the enum : " << house <<  endl;
    cout << "Using Enum to get the value of White and Black respectively: " << Color::COLOR_WHITE 
         << "\t" << Color::COLOR_BLACK << endl;
    
    //--- Bitwise manipulations
    std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    bits.set(3); // set bit position 3 to 1 (now we have 0000 1101)
    bits.flip(4); // flip bit 4 (now we have 0001 1101)
    bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)
 
    std::cout << "All the bits: " << bits << '\n';
    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';

    //--- function as Argument to function
    cout << addThreeNumbers(addTwoNumbers, 3) << endl;

    //--- Create and execute thread
    thread th1 (executeThread, 1);
    thread th2 (executeThread, 2);
    //Join the above threads to the main thread so that the main thread waits
    //for them to complete.
    //Once the threads are joined the code beyond this point will be executed
    //synchronously.
    th2.join();
    th1.join();

    return 0;
}

//---Other---

//--- Debugging
//Use std::cerr instead of std::cout to print errors or while debugging as cerr is non buffered,
//cout is buffered and when an error occurs it may or may not be printed.
//cerr is non buffered and hence has a performance cost but we dont care about performance while
//debugging or when an error actually occurs in our program.

//When adding temporary debug statements, it can be helpful to not indent them.
//This makes them easier to find for removal later.

//Debugging cerrr statements if kept for the full development cycle can clutter the code.
//To use them conditionally we can use preprocessors:
/*
    #define ENABLE_DEBUGGING //Comment out to disable debugging

    #ifdef ENABLE_DEBUGGING
    std::cerr << "function called \n" << endl;
    #endif
*/

//Watching variables with codeblock debugging :
//In Code::Blocks, the watch menu can be found at Debug menu > Debugging windows > Watches. 

//--- Compiler Extensions:
//In brief they are specific to used compilers and might prevent your code from being compatible
//with other compilers.
//To set the comipiler to strict mode that is use no extensions specific to the compiler, we use,
//For GCC-G++ : Adding the -pedantic-errors flag to the compile command line.
//For Code-block : Settings menu > Compiler > Compiler flags tab, then find and check the -pedantic-errors option.

//---Compilation warning flag
//-Wall -Weffc++ -Wextra -Wsign-conversion //Different warning level flags.
//-Werror : This will treat warning as errors and code will not compile. Good for new Learners.

//In Code::Blocks
//From Settings menu > Compiler > Compiler settings tab,
//find and check the options that correlate with -Wall, -Weffc++, and -Wextra
//Go to Other compiler options tab, and add -Wsign-conversion -Werror to the text edit area

//---Language Standard
//Set Language standard globally : Settings menu > Compiler > 
//(Tick/Select) Have g++ follow the C++17 ISO language standard.
//There might be more latest version with 'comming' that can be selected.

//For GCC/G++, 
//pass compiler flags -std=c++11, -std=c++14, -std=c++17,
//or -std=c++2a to enable C++11/14/17/2a support respectively.

//--- Global Variables
//Using extern to define a varaible makes it global in the sence that it can be used between different files.
//Function are already cross file usable, so they must be defined in a namespace to restrict their scope.

//--- Using cin and one getline() after the other.
//When used the buffer from the first cin might not be cleared and will directly be used as the input for
//second getline().
//To prevent this we have to clear the buffer before we use the getline by ignoring the value that is in it.
/*
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
*/
//This will ignore unlimited characters until a \n is removed.

//--- Reference Docs
// Cppreference is a great doc reference for cpp but it is based on community contribution and there might be,
//mistakes, but generally they caught and fixed promptly.

//--- Goto statements
//goto statements can be used in c++ but should be avoided.

//--- Testing
//Code Coverage : Referes to the percentage of statement of the code that is exercised by our test routine.

//--- Arrays
//Arrays should not be initailzed with runtime variables.
//So an array cannot be initialized with user-input with cin or such.
//Some compilers allow this but we can disable it by disabling compiler extension as defined above.

//Even when we want to define the array elements later we should initialize it before : int arr[5]{};

//Arrays passed to functions are demoted to pointer as copying the array might be an expensize operation.

//C++ Arrays do not have a size. This will not work for array passed to function as arguments
//To find size of an array we could use std::size(arrayToFindSizeOf) from <iterator>

//std::array 
//std::array<int, 3> myArray; // declare an integer array with length 3
//array have a size() and sort()

//--- Passing by reference
//When we pass array as an argument to a function we can use 
//void printElements(int (&arr)[4]) : This is passing by reference.
//So that the array does not decay to pointer and we can use size for the array.

//While passsing by reference the compiler adds the * to the pointer so that we get the value directly passed
//to the function.

//Larger data types and classes and structs should be passed by reference as it is faster.

//---Classes
//Fraction fiveThirds{ 5, 3 }; // Brace initialization, calls Fraction(int, int)
//Fraction threeQuarters(3, 4); // Direct initialization, also calls Fraction(int, int)
//Use the brace initialization whenever possible.

//--- Type of initialization
// int value1 = 1; // copy initialization
// double value2(2.2); // direct initialization
// char value3 {'c'}; // uniform initialization