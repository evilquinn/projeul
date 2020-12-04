#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility/string_view.hpp>

#include "../path_def.hpp"

typedef boost::function<bool(const std::string&)> field_validator_type;
typedef std::map<std::string, std::pair<bool, field_validator_type> > passport_fields_type;
bool byr_validator(const std::string& value)
{
    auto vi = 0;
    if ( ! boost::conversion::try_lexical_convert<int>(value, vi) ) return false;
    return 1902 <= vi && vi <= 2002;
};
bool iyr_validator(const std::string& value)
{
    auto vi = 0;
    if ( ! boost::conversion::try_lexical_convert<int>(value, vi) ) return false;
    return 2010 <= vi && vi <= 2020;
};
bool eyr_validator(const std::string& value)
{
    auto vi = 0;
    if ( ! boost::conversion::try_lexical_convert<int>(value, vi) ) return false;
    return 2020 <= vi && vi <= 2030;
};
bool hgt_validator(const std::string& value)
{
    if ( value.size() < 2 ) return false;
    std::string unit(std::prev(value.end(), 2), value.end());
    auto vi = 0;
    if ( ! boost::conversion::try_lexical_convert<int>(value.data(), value.size() - 2, vi) ) return false;
    if ( unit == "cm" ) return 150 <= vi && vi <= 193;
    else if ( unit == "in" ) return 59 <= vi && vi <= 76;
    else return false;
};
bool hcl_validator(const std::string& value)
{
    if ( value.empty() ) return false;
    if ( *value.begin() != '#' ) return false;
    if ( value.find_first_not_of("0123456789abcdef", 1) != value.npos ) return false;
    return true;
};
bool ecl_validator(const std::string& value)
{
    static const std::set<std::string> allowed = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
    return allowed.count(value) != 0;
};
bool pid_validator(const std::string& value)
{
    if ( value.size() != 9 ) return false;
    size_t temp;
    if ( ! boost::conversion::try_lexical_convert<size_t>(value, temp) ) return false;
    return true;
};
bool ignore_validator(const std::string&)
{
    return true;
}
passport_fields_type passport_fields = {
    { "byr", { true,  byr_validator } },
    { "iyr", { true,  iyr_validator } },
    { "eyr", { true,  eyr_validator } },
    { "hgt", { true,  hgt_validator } },
    { "hcl", { true,  hcl_validator } },
    { "ecl", { true,  ecl_validator } },
    { "pid", { true,  pid_validator } },
    { "cid", { false, ignore_validator } } };
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
        if ( field_spec.second.first )
        {
            if ( passport.count(field_spec.first) == 0 )
            {
                return false;
            }
            if ( ! field_spec.second.second( passport.at(field_spec.first) ) )
            {
                return false;
            }
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
