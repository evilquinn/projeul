

#include <iostream>

#include <readline/readline.h>

int main()
{
    std::cout << "hello cpp" << std::endl;
    char *line = readline("Enter a line: ");
    if ( !line ) return 0;
    std::cout << "You wrote: " << line << std::endl;
    free(line);
    return 0;
}
