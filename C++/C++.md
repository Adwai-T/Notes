# C++

## Getting Started

We will first want to install a compiler for C++.

There are a lot of options that we can use, C++ compiler that comes with Visual Studio is a popular option. But we could also use one of the other comilers.

We in this tutorial will use Mingw with Visual Studio Code.

After installing the compiler we want to add the compilers bin folder to the path so that we can use it from our terminal.

> Detailed Explanation on setting up Development enviroment in [Visual Studio Code here](https://code.visualstudio.com/docs/cpp/config-mingw).

## Data Types

```cpp
#include <iostream>
#include <iomanip> // for std::setprecision()

using namespace std;

int main()
{
  //-- Different Ways of Initializing variables
  int a1 = 10;
  int a2= {20};
  int a3 (30);
  int a4;
  a4 = a1 + a2 + a3;
  cout << "Sum => " << a4 << endl;

  //-- Get the size of a datatype in bytes(8bits = 1byte)
  cout << "Size of Int in bytes : " << sizeof(a4) << endl;

  //------ Data Types ------//

  //Integer values signed and unsigned.
  short a;
  int b;
  long c;
  long long d;

  unsigned short e;
  unsigned int f;
  unsigned long g;
  unsigned long long h;

  //-- Boolean
  //Value of 0 or false or NULL is considered false. All other true.
  bool is_true = true;
  bool is_false = NULL;
  cout << "True : " << is_true << endl << "False : " << is_false << endl;

  //-- characters
  char z = 'z';
  int z_num = (int) z; //gives ASC-II based code for z
  cout << z << " ->  " << z_num << endl;

  //-- Floats and doubles
  float i = 0.2f;
  double j = 7.2E5; // => 7.2 * 10^5;
  long double k;
  cout << setprecision(17) << "Double Value (j): " << j << endl;

  //-- Constants
  const double PI = 3.1415;
  //-Enum Constants
  enum { alpha = 9, delta = 5 };
  //Constants that are known at compile time can be declared as constexpr.
  constexpr double gravity { 9.8 };

  //-- Strings
  char str[] = "Adwait";//C like strings
  string str2 = "Sandipan";//string is the part of std library in C++.
  cout << str << " and " << str2 << " are friends." << endl;
}
```

## Strings

Strings in c++ are of two types, string as character array which were used in c or string objects.

When strings are stored as a character array they need a array of size n+1 where n is the number of characters to be stored in the string.

The final character that is stored in the character array is the `\0` also called as the null character, denotes the end of the string. It helps c and c++ identify the end of the string.

We can declare a character array of any length and define every character that we want then end it with null character. When we print this string we will see that the string is only printed till the null character even though we might have an array that is longer.

When we initailize a string or a character array as a string literal we do not need to specify the null character in it, c and c++ will automatically add it.

```cpp
char name[20] = "Jerry";
std::cout << name << std::endl;
char name2[10];
name2[0] = 'T';
name2[1] = 'o';
name2[2] = 'm';
name2[3] = '\0';
name2[4] = 'a';
std::cout << name2 << std::endl;
```

## Static Varaibles

The static storage class instructs the compiler to keep a local variable in existence during the life-time of the program instead of creating and destroying it each time it comes into and goes out of scope. Making local variables static allows them to maintain their values between function calls.

The static modifier may also be applied to global variables. It causes that variable's scope to be restricted to the file in which it is declared.

When static is used on a class data member, it causes only one copy of that variable to be shared by all objects of its class.

## Namespace

Namespace is used for encapsulation.

It helps us organize our code into local groups and prevents name collision that might occur especially when our project are big and we are using external libraries.

We have already seen the `std` name space that is the standard namespace used by C++ library.

```cpp
namespace utils{
    //And then we add all the code that needs to belong to the namespace inside this.
}
```

> While using name space we have to add the name space to both the header file as well as implementation.

## Input From Terminal

```cpp
//--- Getting user input from console.

//-- Using cin
//THis could be a string but we are using the varaible above to store it,
//so it is parsed to integer automatically.
int i;
cout << "Please enter a number to store in i : ";
cin >> i; //value will be implicitly be casted to an int as i is int
//clears the data in the stream.
cin.clear(); 
//We have to use the ignore method of the cin so that the all the data in the stream
//clears and when we use the next cin or getline() the value is reset and we can enter
//a new number.
//cin.ignore(numberOfCharactersToIgnore, ignoreTillReachCharacter);
cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
cout << "You entered : " << i << endl;

//-- Using getline();
string name;
getline(cin, name);
cout << "Your name is : " << name << endl;
```

## String

String are standard objects->class in cpp that has helper methods.

```cpp
//String Functions
//length() -> same as -> size(), append(), insert(index, "value"),
//erase(), replace(index, howManyChar, "value")
//find("value"), substr(start, howLong), compare("compareToValue") -> gives 1 or 0
```

## Conditional Statements

### Ternary Operator

```cpp
//--- Ternary if statement
int num1 = 10;
int num2 = 20;
cout << "Compare Numbers : ";
num1 == num2 ? cout << "Numbers are the same." << endl : cout << "Numbers are different." << endl;
```

## Functions

> Functions need to be declared before they can be used in the code.

A function can be declared initially in the program and defined later in the program. This will allow us to use the function in the program befrore we actually define it.

### Default parameters

```cpp
void helloFunction(std::string message = "Hello World")
{
    cout << message << endl;
}
```

### Overloading

We can have multiple function with the same name that take different parameters. This is called as function overloading.

Function is called according to the arguments passed to the function call.

```cpp
#include <iostream>
using namespace std;

int add(int* a, int* b) {
  int c = (*a) + (*b);
  return c;
}

int add(int* a, int* b, int* c) {
  int d = (*a) + (*b) + (*c);
  return d;
}

int main()
{
  int a = {10}, b = {20}, c;
  c = add(&a, &b);

  int d = add(&a, &b, &c);
  cout << "d : " << d << endl;
}
```

### Passed By Value

When we pass arguments of primitive type as value, the value of the variable is copied into the function and a local varaible for the function is created.

Operations on the values passed by value do not effect the originally declared varaibles.

Also we need to note that the varaibles are scoped for the function and will be cleared once the function is poped off the stack.

```cpp
#include <iostream>

using namespace std;

//--- we can check here that the pointer to a, b and c in add is different,
//as compared to the variables that were passed in main as arguments.
int add(int a, int b) {
  cout << " Pointer a in function add -> " << &a << endl;
  cout << " Pointer b in function add -> " << &b << endl;

  int c = a + b;
  cout << " Pointer c(return value) in function add -> " << &c << endl;
  return c;
}

int main()
{
  int a = {10}, b = {20}, c;
  c = add(a, b);
  cout << "Added Value : " << c << endl;
  cout << " Pointer a in main -> " << &a << endl;
  cout << " Pointer b in main -> " << &b << endl;
  cout << " Pointer c(returned by add) in main -> " << &c << endl;
}
```

### Passing By Reference

```cpp
#include <iostream>

using namespace std;

//'a' in function remains a value,
//'b' is a pointer
int add(int &a, int* b) {
  cout << " Pointer a in function add -> " << &a << endl; //0x22fe4c
  cout << " Pointer b in function add -> " << b << endl; //0x22fe48

  //We add brackets around b so * is not considered as an operation.
  int c = a + (*b);
  cout << " Pointer c(return value) in function add -> " << &c << endl; 
  return c;
}

int main()
{
  int a = {10}, b = {20}, c;
  c = add(a, &b);
  cout << "Added Value : " << c << endl;
  cout << " Pointer a in main -> " << &a << endl; //0x22fe4c
  cout << " Pointer b in main -> " << &b << endl; //0x22fe48
  cout << " Pointer c(returned by add) in main -> " << &c << endl;
}
```

### Passing Arrays as Argument

> Arrays are always passed by reference. Array passed as argument only retain the pointer to the first memory address.

```cpp
#include <iostream>

using namespace std;

//When standard arrays are passed as arguments they downgrade to pointer
//to the first element of the array.
void print(int a[], int size) {
  cout << "Array pointer in print : " << a << endl; //0x22fe30
  
  //arrays get downgraded to just pointer to first element of that array.
  //We have to dereference to get the value of a as it is a pointer.
  cout << "byte size of array a in function : " << sizeof(*a) << endl;

  cout << "[ ";
  for(int i = 0; i < size; i++) {
    cout << a[i] << ", ";
  }
  cout << "\b\b ]";
}

int main()
{
  int arr[5] = { 20, 30, 10, 8, 6 };
  cout << " Array pointer in main : " << &arr << endl; //0x22fe30
  cout << "byte size of array a in main : " << sizeof(arr) << endl;
  cout << "Number of elements in array : " << sizeof(arr)/sizeof(int) << endl;
  print(arr, 5); 
}
```

> Pointers to an array can be incremented to get the pointer to the next element but the array variable cannot be incremented, it will have a compilation error.

## Collections

### Templatized Array

`#include <array>` is where we import templatised array from.

Unlike standard arrays when templatised array are passed to functions they retain their method properties like size.

They have a static size. Once declared the size of templatized array cannot be changed.

We can think of templatised arrays as arrays wrapped inside a object.

### Vector

Vectors can be thought as ArrayList in Java, or arrays in Javascript. They have a varaible size and scale according to elements that we add to the it.

When vectors are passed to an argument directly the vector is copied into a new local variable for that function.

We need to explicitly pass the reference/pointer of the vector to a function so that the same vector in memory is passed.

The initial size of a vector is 10 and it is doubled everytime the size is exceeded.

> When vectors and templatized arrays are assigned to a another variable, a copy of the collection is made and the variable assigned point to that copy. This is not true for standard arrays.

### Standard Array, Templatized Array and Vector

```cpp
#include <iostream>
#include <vector> //Vector
#include <array>//Templatized Array

using namespace std;

void printArray(int a[], int size) {
  cout << "Array pointer in function : " << a << endl; //0x22fe30
  cout << "Size of Array in function : " << sizeof(*a)/sizeof(int) << endl;//1
  cout << "[ ";
  for(int i = 0; i < size; i++) {
    cout << a[i] << ", ";
  }
  cout << "\b\b ] \n\n";
}

//-- Passed by value
//A local copy of the array will be made for the function
void printTemplatizedArray(array<int, 5> a) {
  cout << "Templatized Array pointer in function : " << &a << endl; 
  cout << "[ ";
  for(int i = 0; i < a.size(); i++) {
    cout << a[i] << ", ";
  }
  cout << "\b\b ] \n\n";
}

//-- Passed by reference
//The same vector from the memory will be passed.
void printVector(vector<int> &v) {
  cout << "Vector pointer in print function : " << &v << endl;
  cout << "[ ";
  for(int i = 0; i < v.size(); i++) {
    cout << v[i] << ", ";
  }
  cout << "\b\b ] \n\n";
}

int main()
{
  //--- standard array in c and c++
  int arr[5] = { 10, 20, 30, 40, 50 };
  cout << "Array pointer in main : " << &arr << endl; //0x22fe30
  cout << "Size of array in main : " << sizeof(arr)/sizeof(int) << endl;//5
  printArray(arr, sizeof(arr)/sizeof(int));

  //--- templatized arrays
  array<int, 5> temp_arr = { 1, 2, 3, 4, 5 };
  cout << "Templatized Array pointer in main : " << &temp_arr << endl;
  printTemplatizedArray(temp_arr);

  //--- Vector
  vector<int> vec = { 1, 2, 3, 4, 5 };
  vec.push_back(9);
  cout << "Vector pointer in main : " << &vec << endl;
  printVector(vec);
```

## Object Orineted Programming

> When we declare structs and classes, they are instantiated automatically and a local variable for the instace is created in the local scope where it is declared. We do not need to use the `new` keyword. Using the `new` keyword will create a dynamic object in the heap which we have to manage the memory for.

### Structs

Structs are mostly used for small object definitions.

Structs variables are by default public where class varaibles by default are private.

Structs mostly are used as PODS : Plain old data structures

```cpp
#include <iostream>
#include <string> //for converting int to string.

using namespace std;

struct Vehicle {
  static int numberOfRegisteredVehicles;
  string name;
  int id;
  Vehicle(string name, int id, string type) {
    this->name = name;
    this->type = type;
    this->id = id;
    numberOfRegisteredVehicles++;
  }
  Vehicle() {}
  void setType(string type) {
    this->type = type;
    numberOfRegisteredVehicles++;
  }
  string getType() {
    return type;
  }
  string toString() {
    string output;
    output = "Name : " + name + " \t type : " + type + "\t Id : " + to_string(id);
    return output;
  }
private:
  string type;
};

//We have to declare static outside of the class as below.
int  Vehicle::numberOfRegisteredVehicles = 0;

int main()
{
  //Initialize, we don't use new.
  Vehicle veh1;
  veh1.name = "6wheeler";
  veh1.id = 20;
  veh1.setType("Truck");
  cout << veh1.toString() << endl;

  Vehicle veh2("City Bus", 10, "Bus");
  cout << veh2.toString() << endl;
}
```

## Classes

By default variables declared in a class are private variables.

### Operator Overloading

Operators can be overloaded to define how they work when used with the given class.

The example below shows a comparison operator that compares this instance with the given instance for equality.

### Friend Functions and classes

`friend` function are function that are declared in the class and have access to the private variables of the class it is declared in, but we define it outside the class.

> Friends are functions or classes declared with the `friend` keyword.

It Also should be noted that it is not a instance function but its own individual function.

As it is not a instance function we have to pass in the instace so we know which instance we are refering to.

### Inheritance

We define inheritance like `class Rectangle: public Polygon { /* ... */ }`.

In the above case we declare the parent class with an access modifier of `public`, this means that class will inherit all the members with the same levels they had in the base/parent class.

With `protected`, like `class Daughter: protected Mother;`, all `public` members of the base class are inherited as `protected` in the derived class. Conversely, if the most restricting access level is specified (`private`), all the base class members are inherited as `private`.

When inheritance level is defined as public, the methods not inherited from parent are :

* its constructors and its destructor
* its assignment operator members (operator=)
* its friends
* its private members

#### Multiple Inheritance

A class may inherit from more than one class by simply specifying more base classes, separated by commas, in the list of a class's base/parent classes.

`class Rectangle: public Polygon, public Output;`
`class Triangle: public Polygon, public Output {}`

### Abstract and Concrete Classes

Abstract Classes provide an appropriate base class from which other classes can inherit. Abstract classes cannot be used to instantiate objects and serves only as an interface.

Classes that can be instantiated are called as concrete classes. They can inherit from abstract classes overide their methods.

A class is made abstract by declaring at least one of its functions as pure **virtual function**.

A pure virtual function is specified as `virtual double getArea() = 0`.

### Example Class

```cpp
#include <iostream>
#include <string> //for converting int to string.

using namespace std;

class Animal
{
private:
  string name;

public:
  Animal() {}
  string getName()
  {
    return name;
  }
  void setName(string name)
  {
    this->name = name;
  }
  void drink() {
    cout << "Animal is drinking water." << endl;
  }
  void eat(string food)
  {
    cout << name << " is eating " << food << "." << endl;
  }
  // Makes the animal class abstract.
  //  =0 makes this a pure virtual function.
  virtual void talk() = 0;
};

class Dog : public Animal
{
private:
  int age;

public:
//--Constructor
  Dog(string name, int age)
  {
    this->setName(name);
    this->age = age;
    cout << getName() << " has come to visit." << endl;
  }
//--Destructor
  ~Dog() {
    cout << getName() << " has run away." <<endl;
  }
  void talk()
  {
    cout << this->getName() << " is barking." << endl;
  }
  int getAge()
  {
    return age;
  }
  void drink()
  {
    cout << getName() << " is drinking water." << endl;
  }
  friend int dogAgeCalc(Dog &dog);
  friend void goodDog(Dog dog);
};
//If not passed by reference the dog object will be copied
int dogAgeCalc(Dog &dog)
{
  cout << "Pointer in friend funtion(passed by reference): " << &dog << endl;//0x22fd30
  return dog.age * 5;
}
void goodDog(Dog dog)
{
  cout << "Pointer in friend funtion(passed by value) : " << &dog << endl;//0x22fd30
  cout << dog.getName() << " is a good boy." << endl;
}
main()
{
  Dog spike("Spike", 5);//constructor.
  spike.talk();//overrider parent abstract method.
  spike.drink();//override parent method.
  cout << "Pointer in main 1 : " << &spike << endl;//0x22fd30
  //-- friend method
  int spikesAgeInHumanYears = dogAgeCalc(spike);//passed by reference
  goodDog(spike);//passed by value, Dog obj copied to function

  /*
  * When we call goodDog function the object spike is copied,
  * so no constuctor is called.
  * But once the function goes out of scope,
  * the copy of the spike object for the function is destroied,
  * and the destructor for that instance is called.
  * Finally before main goes out of scope destructor for spike
  * instance is called and object is destroied from memory. 
  */

  cout 
    << spike.getName() 
    << " age in human years is " 
    << to_string(spikesAgeInHumanYears) 
    << endl;
  cout << "Pointer in main 2 : " << &spike << endl;//0x22fd30
}
```

## Template Classes

Template classes help us make generalized classes that can be used with different data types.

We have already seen example of template class in the form of vectors and templatized array. They take a type when we declare them and can store that datatype within them while ensuring type safety in our program.

Lets consider an example of a Stack. We want to create a Stack implementation that can hold any datatype.

### Example Template class

```cpp
#include <iostream>
#include <string> //for converting int to string.
#include <vector>
#include <iterator> //iterator for iterating over vector

using namespace std;

template <class T>
class Stack
{
private:
  vector<T> stack;
public:
  void push(T const &);//pass by reference
  void pop();
  T peek() const
  {
    return stack.back();
  }
  bool isEmpty()
  {
    return stack.empty();
  }
  void print();
};

template <class T>
void Stack<T>::print()
{
  cout << " { ";
  //type name is used to tell compiler that this is a type declaration
  //as compiler will interpret it as function call.
  typename vector<T>::iterator stackT;
  for (stackT = stack.begin(); stackT < stack.end(); stackT++)
  {
    cout << to_string(*stackT) << ", ";
  }
  cout << "\b\b }" << endl;
}

template <class T>
void Stack<T>::push(T const &t)
{
  stack.push_back(t);
}

template <class T>
void Stack<T>::pop()
{
  if (stack.empty())
  {
    throw out_of_range("Empty stc");
  }

  stack.pop_back();
}

int main()
{

  Stack<int> stack;

  stack.push(7);
  int a{9}, b{6}, c{8};
  stack.push(a);
  stack.push(b);
  stack.push(c);
  stack.print();
  stack.pop();
  cout << "Pop" << endl;
  stack.pop();
  cout << "Pop" << endl;
  stack.print();
}
```

## typename

> Only use the keyword typename in template declarations and definitions.

Let take an [example](https://www.ibm.com/docs/en/i/7.3?topic=only-typename-keyword-c).

```cpp
template<class T> class A
{
  T::x(y);
  typedef char C;
  A::C d;
}
```

The statement `T::x(y)` is ambiguous.

It could be a call to function `x()` with a nonlocal argument `y`, or it could be a declaration of variable `y` with type `T::x`. C++ will interpret this statement as a function call.

In order for the compiler to interpret this statement as a declaration, you would add the keyword typename to the beginning of it.

## Template Function

Similar to template classes we have seen above we can also have template functions.

Lets consider the example of quicksort function below.

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

template<class T> void quicksort(T a[], const int& leftarg, const int& rightarg)
{
  if (leftarg < rightarg) {

    T pivotvalue = a[leftarg];
    int left = leftarg - 1;
    int right = rightarg + 1;

    for(;;) {

      while (a[--right] > pivotvalue);
      while (a[++left] < pivotvalue);

      if (left >= right) break;

      T temp = a[right];
      a[right] = a[left];
      a[left] = temp;
    }

    int pivot = right;
    quicksort(a, leftarg, pivot);
    quicksort(a, pivot + 1, rightarg);
  }
}

int main(void) {
  int sortme[10];

  for (int i = 0; i < 10; i++) {
    sortme[i] = rand();
    cout << sortme[i] << " ";
  };
  cout << endl;

  quicksort<int>(sortme, 0, 10 - 1);

  for (int i = 0; i < 10; i++)
    cout << sortme[i] << " ";
  cout << endl;
  return 0;
}
```

## Memory Management In C++

Before we try to understand pointer we need to understand how C++ manages memory.

When we run our c++ program it gets assigned a process by our operating system, each process is allocated some memory.

Following are the segements that our program will divide the memory.

* Code/Text :

This section holds our code as instructions that will be executed by the process assigned to our program by our operating system.

A function is divided into a set of contigious instructions.

The instuctions are read only and are shared by the program.

* Global/Static data :

This segement holds the global and static data.

* Stack :

Memory is assigned on the stack to the function variable when they come into scope and removed from stack when that function goes out of scope.

So we can say that memory management in stack is automatic and we do not need to clean memory for variables that are stored in stack. Memory is reclaimed when function responisble for creating those variables goes out of scope.

* Heap :

Heap is where dynamically created object are stored.

When we create an object dynamically during runtime with new, malloc, calloc or realloc, memory is reserved on the heap and the object are created.

Any objects created on heap have to be managed by us and cleaned when they are no longer needed. Not cleaning these objects can cause memory leaks.

## Pointers

Pointers are variables that store the memory address of another variable.

```cpp
#include <iostream>
#include <string> //for converting int to string.

using namespace std;

int main()
{
  int a{10};
  cout << "Initial value of a : " << a << endl;//10
  int* ptr_a = &a;//pointer to a;
  *ptr_a = 5;
  cout << "Value of a changed with pointer dereferencing : " << a << endl;//5
}
```

> Pointer variables are strongly typed. That means a pointer to int variable should be of type int.

Pointer variables are strongly typed as the compiler needs it to get the value when we dereference the pointer.

Lets understand it with a pointer to a `char` and an `int`. An `int` in c++ is of 4 bytes, where as a `char` is 1 byte.

Thus c++ will use the type of the pointer to determine how many bytes it needs to consume after the inital pointer to produce the required data.

It also is necessary for performing arithematic operations on pointers.

For example in the case on an `int` pointer, an increment by 1 will increament the value of pointer by 4 as an int is stored as 4 bytes in the memory.

This is an important property of pointers as it is used when we are dealing with array pointers to get to the next element in the array.

### Generic pointer

Generic pointer is designated by `void`.

They can then be type casted to convert the pointer into required type pointer. As we have seen above it is necessary for c++ to know what type of data the pointer point to, to dereference and get the value.

```cpp
int a{10};
void* ptr = &a;//pointer to a;
int* ptr_a = (int*) ptr;
*ptr_a = 8;
cout << "Value of a changed with pointer dereferencing : " << a <<endl;//8
```

### Pointer to Pointer

We can also have a pointer to another pointer as they are also stored in memory somewhere.

> A typical pointer is stored in 4 bytes.

```cpp
int a{10};
int* ptr = &a;//pointer to a;
int** ptr_ptr = &ptr;//pointer to pointer of a
/*We increase the number of stars to the level of pointers*/
**ptr_ptr = 8;//dereferencing to update value of a
cout << "Value of a changed with pointer dereferencing : " << a <<endl;//8
```

### Pointer as Arguments

We have already seen passing a pointer to a function. It is called as passing as reference to a function as we are not passing the actual object but a pointer reference to the object.

This prevents the variable from getting copied to the local scope of the function.

### Array and Pointer relation

Following example code shows how arrays and pointers work together and how arithematic opeartions on pointers help in traversing the array.

```cpp
int arr[5]{10, 20, 30, 40, 50};

int* ptr = arr;
std::cout << "Pointer to arr : " << ptr << std::endl;//0x22fe30
std::cout << "Pointer to first element in arr : " << &arr[0] << std::endl;/0x22fe30
//We can perform arithematic operation in the array pointer.
std::cout << "2nd element in array : " << *(ptr+2) << std::endl;//30
//or
std::cout << "3rd element in array : " << *(arr+3) << std::endl;//40
//same as
std::cout << "3rd element in array : " << arr[3] << std::endl;//40
```

When arrays are passed as argument to a function they get downgraded to just pointer to the first element of that array.

> Pointers to an array can be incremented to get the pointer to the next element but the array variable cannot be incremented, it will have a compilation error.

### Function Pointers

Function are sets of instructions stored in the code/text section of the memory managed by the c++ program.

We can get a pointer reference to function like we can for any other variable and even pass them as argument to other functions.

This functions passed as arguement can be used as callback functions.

```cpp
#include <iostream>

using namespace std;

void print()
{
  cout << "Printed." << endl;
}
void doubleNum(int &a)
{
  a *= 2;
  cout << "Doubled number : " << a << endl;
}

void a(void (*p)())
{
  p();
}

void b(void (*p)(int &), int num)
{
  p(num);
}

int main()
{
  a(print);
  b(doubleNum, 3);
}
```

## Dynamic Memory

Dynamic memory or heap is where dynamically created variables are stored.

We can create any number of variables in dynamic memory at runtime as long as our computer has more memory to share.

> Compared to variables stored in stack and global variables, variables stored on the heap are slower.

### C and C++ ways

There are different ways in c and c++ by which we can allocate dynamic memory to our objects.

C uses functions like `malloc()`, ``calloc()` and `realloc()` to assign/reserve memory and return a pointer, and uses `free()` to destroy the variable and return the memory to the system.

C++ introduced the `new` keyword to assign/reserve memory for dynamic variable/objects and `delete` or `delete()` to destroy the variable and return the memory to the sytem for use.

There are fifference between c functions and c++ keywords in how they work.

`new`

* Calls constuctor.
* is an Operator.
* Returns exact data type.
* on failure, throws bad_alloc exception.
* Size is calcuated by compiler.

`malloc()`, `calloc()` and `realloc()`

* does not call constructors.
* It is a function.
* Returns void*.
* On failure, returns NULL.
* size is calculated manually.

`delete()`

* It is an operator.
* It deallocates memory dynamically.
* Used for null pointers or memory assigned by new operator.
* calls desturctor after destoring allocated memory.
* Faster.

`free()`

* It is library function.
* destories memory at runtime.
* used with null pointers or memory allocated by using malloc().
* Only frees momory from the heap.
* comparatively slower.

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Box 
{
  int side;

  public:
    int* ptr;

    //Constructor
    Box()
    {
      cout << "Construtor Called" << endl;
    }

    ~Box() {
      cout << "Destructor Called" << endl;
    }
};

int main()
{

  //Initializing primitive data types with new
  int *num = new int{10};
  cout << *num << endl;//10
  delete num;
  cout << *num << endl << endl;//prints garbage value

  //Create Object With new operator
  Box* box = new Box;
  //Destory Object using delete
  delete(box); //also can use delete box;
  cout << "\n" << endl;


  cout << "Using malloc() and free() : " << endl;
  //Create Object using malloc()
  Box* box2 = (Box*)malloc(sizeof(Box));
  //Free up memory using free()
  free(box2);
  cout << "No Construtor or Destructor is called." << endl;
  cout << "\n" << endl;


  //Create an object using Class name
  cout << "Using Class Name : " << endl;
  Box box3;//don't need to manage memory, scoped variable.
  cout << "\n" << endl;

  cout << "End of main function. box3 will go out of scope now." << endl;
  return 0;
}
```
