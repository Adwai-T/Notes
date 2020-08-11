#include <iostream>

//Dynamic memory are a little slower than that of statically alloted memory.
//But the limit to how much memory can be allotted is the available virtual memory.

using namespace std;

//Forward declaration for some reason does not work with dynamic memory allocation.
class Rectangle{

    int width;
    int height;

    public:

        Rectangle(int width, int height){
            this->width = width;
            this->height = height;
        }

        int area(){
            return width * height;
        }

        ~Rectangle(){
            cout << "Rectangle Object Destroied." << endl;
        }
};

int main(){
    
    //--- new
    //The new special operator allots memory and returns the memory address of the allotted memory.
    //If new is used to allot memory to an object the object is also created in the memory.
    //This is a major difference between the malloc() function from C that only allots memory and still can be used.
    double* number_1 = NULL; //Pointer initialized with null
    number_1 = new double;//Request memory for the vairable.
    *number_1 = 3.141576;
    
    cout << "Double Value from the pointer : " << *number_1 << endl;

    delete number_1; //Free up memory.

    //--- Class object dyanamic memory allocation
    Rectangle *square = NULL;
    square = new Rectangle(10, 12);

    //As square by-itself is a memory address we access area by using ->
    cout << "Area of square : " << square->area() << endl; 

    delete square;  

    return 0;
}

