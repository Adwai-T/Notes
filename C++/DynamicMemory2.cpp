
/*
  Use Of new, delete and malloc(), free()
*/

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
  cout << "Initialize Int using new : " << endl;
  int *num = new int{10};
  cout << *num << endl;

  cout << "Using new and delete : " << endl;
  //Create Object With new operator
  Box* box = new Box;

  //Destory Object using delete
  delete(box);
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
  Box box3;
  cout << "\n" << endl;

  /*
    When we create an object with Class-Name Object-Name a block
    is created, the object has a automatic storage duration that is
    automatically destroyed on going out of scope.
    But when we use new Class-Name the object has a dynamic storage
    duration which means one has to delete it explicitly using delete.

    In case where we create a object using new we have to use the
    delete function to delete the object and free memory as it will
    not be deleted automatically and no destructor will be called even
    when the object goes out of scope.
  */

  return 0;
}

/*
  Difference Between malloc and new || free and delete

  New and Delete operator in C++ to allocate memory where as malloc
  and free function are used for same purpose in C and can be used
  in C++

  new
    * Calls constuctor
    * is an Operator
    * Returns exact data type
    * on failure, throws bad_alloc exception
    * Size is calcuated by compiler
  
  malloc()
    * does not call constructors
    * It is a function
    * Returns void*
    * On failure, returns NULL
    * size is calculated manually
    
  delete()
    * It is an operator
    * It deallocates memory dynamically
    * Used for null pointers or memory assigned by new operator
    * calls desturctor after destoring allocated memory
    * Faster

  free()
    * It is library function
    * destories memory at runtime
    * used with null pointers or memory allocated by using malloc()
    * Only frees momory from the heap
    * comparatively slower
*/