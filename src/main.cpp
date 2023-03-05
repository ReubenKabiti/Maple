#include <iostream>
#include "file.hpp"

int main(int argc, char ** argv)
{
    File file("test.txt");
    file.open(File::ReadOnly);
    while(!file.isAtEnd())
    {
        std::cout << file.read();
    }
    return 0;
}