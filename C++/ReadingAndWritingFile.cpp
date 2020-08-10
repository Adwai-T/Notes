#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string get_message(string message)
{
    return message;
}

int main()
{
    ofstream file;
    ifstream readFile;

    file.open("hello.txt");
    //The above could be done in one line
    //ofsream file("hello.txt");

    //We can use the file write as if it was cout.
    if(file.is_open())
    {
        file << "Hello There";
        cout << "File write Successful." << endl;
    }
    //Files are closed automatically at the end, but we could be explicit.
    file.close();

    cout << get_message("Printing Message") << endl;



    return 0;
}

