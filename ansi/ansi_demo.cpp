
#include <iostream>
#include <iomanip>
#include "escapes.hpp"

int main()
{
    std::cout << "hello" << std::endl;

    std::cout << "Basic 8 colours:" << std::endl;
    for ( int i = 30; i < 38; ++i )
    {
        std::cout << ansi_escapes::colour::by_arg(i) << std::setw(4) << i;
    }
    std::cout << std::endl;
    std::cout << "Bright colours:" << std::endl;
    for ( int i = 30; i < 38; ++i )
    {
        std::cout << ansi_escapes::colour::brighten(ansi_escapes::colour::by_arg(i)) << std::setw(4) << i;
    }
    std::cout << std::endl;
    std::cout << ansi_escapes::colour::reset() << std::endl;
    
    std::cout << "256 colours:" << std::endl;
    for ( int i = 0; i < 16; ++i )
    {
        for ( int j = 0; j < 16; ++j )
        {
            int v = i * 16 + j;
            std::cout << ansi_escapes::colour::by_arg_256(v) << std::setw(4) << v;
        }
        std::cout << ansi_escapes::colour::reset() << std::endl;
    }
    std::cout << std::endl;
    std::cout << ansi_escapes::colour::reset() << std::endl;
    
    return 0;
}