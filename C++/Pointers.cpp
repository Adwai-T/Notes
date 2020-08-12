#include <iostream>

using namespace std;

int main()
{
    int a = 10;// Actual value
    int* b = &a;//Pointer.
    int c = *b;//Get value that is stored at the memeory address held by pointer.

    cout << "A : Value : " << a << endl;
    cout << "B : Pointer : " << b << endl;
    cout << "C : Value from Pointer : " << c << endl;

    //---Arrays Pointers
    //In C++ Array are primitive and could be looked as if they were just pointer.
    int arr[5] = { 1, 2, 3, 4, 5 };

    //Both give the same memory address.
    //As arrays in C++ are just pointers to the memory location in which data is stored.
    int *arr_index_1 = &arr[0];
    int *arr_start = arr;
    cout << "Pointer to the index 0 of array : " << arr_index_1 << endl;
    cout << "arr printed direcly : " << arr_start << endl;
    cout << "arr printed with *arr : " <<  *arr << " : Printes the value of index 0 of the array." <<endl;
    cout << "Incrementing array or pointer value by 1 : *(arr+1) : " << *(arr+1) << endl;

    cout << "end of program";

    return 0;
}
