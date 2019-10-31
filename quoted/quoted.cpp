
#include <iostream>
#include <vector>
#include <sstream>
#include <boost/io/detail/quoted_manip.hpp>

int main()
{
    std::string the_string = "this is the value";
    std::vector<std::string> strings;
    strings.emplace_back(the_string);

    for ( size_t i = 0; i < 5; ++i )
    {
        std::ostringstream ss;
        ss << boost::io::quoted(strings[i]);
        strings.emplace_back(ss.str());
    }
    for ( auto&& str : strings )
    {
        std::cout << str << std::endl;
    }
    return 0;
}
