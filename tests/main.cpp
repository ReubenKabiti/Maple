#include "file.hpp"
#include <iostream>

int main()
{
    File file("test.txt");
    file.open(File::ReadOnly);

    while(!file.isAtEnd())
    {
        std::cout << file.read();
    }
    std::cout << std::endl;
    return 0;
}