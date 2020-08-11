//Structs and Classes
//Structs variables are by default public where class varaibles by default are private.
//Structs are used for smaller objects.
//Structs mostly are used as PODS : Plain old data structures

//There are no particular specific getters and setters keywords in C++. 

//--- Class Templates
/*
    template <class type> class class-name {
        .
        .
        .
    }
*/

#include <iostream>
#include <string>

using namespace std;

//--- Struct
struct User
{
    string first_name;
    string last_name;
    int age;
    string get_status()
    {
        return status;
    }

    private: 
        string status = "new";
};

class OOP
{
    static int users;
    string name = "Adwait";
    string status = "Gold";

    public:
        int age = 26;
        string get_status()
        {
            return status;
        }

        string get_name()
        {
            return name;
        }

        static int get_users()
        {
            return users;
        }

        //--- Constructor
        OOP(string name, string status)
        {
            this->name = name;
            this->status = status;
            users++;
        }

        //--- Desctructor
        ~OOP()
        {
            cout << "Object Destroied \t" << this->name << endl;
            users--;
        }

        //--- Operator overloading
        //Operator overloading can be done for all operators + - * == etc
        bool operator ==(OOP oop)
        {
            if(oop.get_name() == this->get_name())
            {
                return true;
            }
            else return false;
        }

        //--- Friend methods
        //They allow us to define a function related to this class that has access to this classes
        //private varibles outside of the class.
        //We just declare the function and then we define the funtion outside of the class.
        friend void print_status(OOP user);
};

//Define the friend function
//We also cannot call the function as "user.print_status" as it is not a method of the instance,
//but a individual function that has access to the private data of that instance.
//So we have to pass the instance as an argument to know which instance we want to use it with.
void print_status(OOP user)
{
    cout << "The Status from the friend function is : " << user.status << endl;
}

//--- Function simialar to toString() method for objects in java.
//Similar function can be done for istream that is cin.
ostream& operator << (ostream& output ,User user)
{
    output << "FirstName : " << user.first_name << " Age : " << user.age << " Status : " << user.get_status() <<  endl;
    return output;
} 

//Static members of a class are not alloted memory until we call them in code.
//That is why we cannot actually initialize a static member varible of a class inside of the class.
//Thus before we can use the static memeber we have to initialize it.
int OOP::users = 0;

int main()
{

    //--- initializing and using struct
    User me;
    me.age = 26;
    me.first_name = "Axle";
    me.last_name = "Car";

    cout << "Status is : " << me.get_status() << endl;
    cout << "User struct printed from function : similar to toString() in java : ";
    cout << me;

    //--- Initializing and using class.
    //Unlike Java, C# and many other languages we do not have to use the new keywork
    //to create a new object from the class.
    //We just defined the class as if it was a datatype and objects instances are created.
    OOP user_me("Adwait", "Active");
    
    //Multiple Objects/Classes can be instanctiated inline like below.
    OOP user1("user1", "notActive"), user2("user2", "maybe"), user3("user3", "may");

    cout << "The Details from object instance : " << user_me.get_name() << "\t" << user_me.get_status() << endl; 

    cout << "Number of instances of the OOP class : " << OOP::get_users() << endl;

    //WE could implicitely call the descructor But it does not actually destory the instance from memory.
    //THis will demonstrate:
    user1.~OOP();
    cout << "Number of instances of the OOP class After destruction is called : " << OOP::get_users() << endl;

    //Compare with overloaded operators
    OOP user_1("Axil", "active"), user_2("Axil", "active"), user_3("Abhi", "inactive");
    user_1 == user_2 ? cout << "The users are equal." << endl : cout << "The users are different." << endl;
    user_1 == user_3 ? cout << "The users are equal." << endl : cout << "The users are different." << endl;

    print_status(user_1);

    return 0;
}

//If we want to separate our classes into different files
//-  we create a new File advisably witht the same name as the class defined in it.
//- create a header file with the same name with the extension .h
//- Let the header file onlyc ontaine the class and methods declarations.
//- To avoid a file being added to the project or imported more than once we have :
/*

#ifndef CLASSNAME_H
#define CLASSNAME_H

----call code here----

#endif
*/
//- Let the cpp file that is the class file contain all the definitions of the class.
//- where ever we want to use the class we include the class header file as #include "headerfile.h"

//--- Inheritance
/* class Teacher : public OOP
{

}
*/

// virtual keywork is used to overide the function from the parent class in the child class.
//conider that both teacher and OOP has the output methods.
/*
virtual void output();//defined in parent class.

Teacher teacher;
OOP& user = teacher;

user.output(); //Because of the virtual keyword we will have output method from the teacher instance.
//If virtual was not put then we will have the output method from the parent class executed/called.
*/
