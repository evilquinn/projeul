

#include <iostream>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    std::cout << "hello cpp" << std::endl;
    for ( size_t i = 0; i < 10; ++i )
    {
        char *line = readline("");
        if ( !line ) return 0;
        if ( strlen(line) == 0 ) continue;
        add_history(line);
        free(line);
    }
    return 0;
}
