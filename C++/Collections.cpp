#include <iostream>
#include <vector>
//For using standard array we do not use this import.
//This import is for the templatized array.
#include <array> 

//Vectors are similar to List or ArrayList in Java.

//When standard arrays are passed as arguments they downgrade to pointer to the first element of the array.

//Templatised array are in between standard array in how they work.
//When passed as argument they have a reference to the memory of the array and thus size of the array
//could be determined.
//But like standard array they have a static size.
//They are just arrays wrapped in an object.

//If we pass the vector as an argument direclty the vector is copied and creates
// a new vector.
//So we need to use '&' sign before the parameter so that the memory is passed or,
//the vector is passed by reference.
//Passing by reference works similarly for a templatized array.
void print_vector(std::vector<int> &data){

    //Unlike for arrays the size of the vector can be accessed from the passed argument.
    for(int i = 0; i < data.size(); i++){
        std::cout << data[i] << std::endl;
    }

    std::cout << "\n";
}

int main()
{

    //--- Normal array
    int arr [] = { 1, 2, 3 };
    //We could pass in the size of the array if the required size of the array is bigger than
    //the number of declared variables.
    std::cout << "This is an element from standard array : " << arr[0] << std::endl;
    //The normal arrays dont have a size method;

    //--- Templatized array
    //We put the datatype and the size of the array inside of <> while declaraing the array.
    std::array<int, 10> array_data = { 1, 5, 6 };
    std::cout << "Element from the templatized array is  : "<< array_data[2] <<  std::endl; 
    //Unlike vectors the size of the templatized array actually gives us the total size of the array and
    //not the number of elements that have been added.
    std::cout<< "Size of the templatized array : "<< array_data.size() << std::endl;

    std::vector<int> data = { 10, 12 };
    data.push_back(14);

    std::cout << "Number from the array  is : " <<  data[0] << std::endl;

    print_vector(data);

    return 0;
}


//Some Other important differences : 
/* 
    Unlike Java the vectors and templatized array when assigend to another variable,
    both the variables point to different vectors in memory as they are copied and not,
    Just point to the same data in memory.
    This is true for templatized array and for vectors, but not for standard or normal C style arrays.
*/