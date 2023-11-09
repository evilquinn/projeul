
#include <iostream>
#include <cerrno>
#include <cstring>
#include <thread>

#include <dirent.h>

int main()
{

    const char* dir_name = ".";
    DIR* directory = opendir(dir_name);
    if ( !directory ) throw std::runtime_error(std::string("opendir(\"") + dir_name + "\") failed: " + std::strerror(errno));

    std::cout << "entries in \"" << dir_name << "\":" << std::endl;
    for(;;)
    {
        errno = 0;
        dirent* entry = readdir(directory);
        if ( !entry && errno ) throw std::runtime_error(std::string("readdir failed: ") + std::strerror(errno));
        if ( !entry ) break;
        std::cout << entry->d_name << std::endl;
    }

    if ( closedir(directory) == -1 ) throw std::runtime_error(std::string("closedir failed: ") + std::strerror(errno));

    return 0;
}


