#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

#include "../path_def.hpp"

typedef std::map<std::string, bool> passport_fields_type;
passport_fields_type passport_fields = {
    { "byr", true  },
    { "iyr", true  },
    { "eyr", true  },
    { "hgt", true  },
    { "hcl", true  },
    { "ecl", true  },
    { "pid", true  },
    { "cid", false } };
typedef std::map<std::string, std::string> passport_type;

std::ostream& operator<< (std::ostream& os, const passport_type& passport)
{
    if ( !os ) return os;
    os << "passport: {";
    for ( auto&& field : passport )
    {
        os << " " << field.first << ":" << field.second;
    }
    os << " }";
    return os;
}


void parse_passport_line(const std::string& line, passport_type& passport_type)
{
    auto token_begin = line.begin();
    for ( auto token_end = std::find(token_begin, line.end(), ' ');
          std::distance(token_begin, token_end) > 0;
          token_end = std::find(token_begin, line.end(), ' ') )
    {
        auto token_sep = std::find(token_begin, token_end, ':');
        passport_type[std::string(token_begin, token_sep)] = std::string(std::next(token_sep), token_end);
        token_begin = token_end;
        if ( token_begin != line.end() ) ++token_begin;
    }
}
passport_type parse_passport(std::istream& is)
{
    std::string line;
    passport_type result;
    while ( std::getline(is, line) )
    {
        if ( line.empty() ) break;
        parse_passport_line(line, result);
    }
    return result;
}

bool is_valid(const passport_fields_type& fields, const passport_type& passport)
{
    for ( auto&& field_spec : fields )
    {
        if ( field_spec.second &&
             passport.count(field_spec.first) == 0 )
        {
            return false;
        }
    }
    return true;
}


int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/04_input.txt");
    size_t result = 0;
    while ( inf )
    {
        auto passport = parse_passport(inf);
        std::cout << passport << "\n";
        if ( is_valid(passport_fields, passport) ) ++result;
    }
    std::cout << "result: " << result << std::endl;
    return 0;
}
