#include <iostream>
#include <fstream>
#include <vector>
#include <boost/utility/string_view.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "../path_def.hpp"

struct policy
{
    int first;
    int second;
    char val;
};
std::ostream& operator<< ( std::ostream& os, const struct policy& p)
{
    if ( os )
    {
        os << "first: " << p.first << ", second: " << p.second << ", val: " << p.val;
    }
    return os;
}
struct password
{
    struct policy policy;
    std::string password;
};
std::ostream& operator<< ( std::ostream& os, const struct password& p)
{
    if ( os )
    {
        os << "policy: { " << p.policy << " }, password: " << p.password;
    }
    return os;
}
struct password password_from_string(const std::string& policy_str)
{
    static const boost::regex pattern("^([\\d]*)-([\\d]*) ([a-zA-Z]): ([a-zA-Z]*)$");
    boost::smatch groups;
    if ( boost::regex_search(policy_str, groups, pattern) )
    {
        return password { policy{ boost::lexical_cast<int>(groups[1]),
                                  boost::lexical_cast<int>(groups[2]),
                                  *groups[3].first },
                          groups[4] };
    }
    throw std::runtime_error(std::string("failed to parse policy from: ") + std::string(policy_str));
}
bool validate_password_v1(const struct password& p)
{
    int occurs = std::count(p.password.begin(), p.password.end(), p.policy.val);
    return p.policy.first > occurs || p.policy.second < occurs;
}
bool validate_password_v2(const struct password& p)
{
    bool first_is = p.password.at(p.policy.first - 1) == p.policy.val;
    bool second_is = p.password.at(p.policy.second - 1) == p.policy.val;
    return first_is != second_is;
}


int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/02_input.txt");
    std::vector<struct password> data;
    for (std::string line; std::getline(inf, line); )
    {
        data.emplace_back(password_from_string(line));
    }
    size_t result_v1 = 0;
    size_t result_v2 = 0;
    for ( auto&& datum : data )
    {
        if ( validate_password_v1(datum) )
        {
            ++result_v1;
        }
        if ( validate_password_v2(datum) )
        {
            ++result_v2;
        }
    }

    std::cout << "result_v1: " << result_v1 << std::endl;
    std::cout << "result_v2: " << result_v2 << std::endl;
    return 0;
}
