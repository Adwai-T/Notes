#include <iostream>
#include <cstdlib>

int main()
{
    std::cout << "Random number generator";
    for(int i = 0; i <= 10; i++){

        std::cout << rand() << std::endl;
    }
    return 0;
}
