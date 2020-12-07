/*
 * https://adventofcode.com/2020/day/6
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include <aoc/path_def.hpp>

struct bag
{
    std::string adj;
    std::map<std::string, int> contains;
};

int count_can_contain(const std::vector<bag>& bags, std::string containee)
{
    std::set<std::string> containers;

    auto curr_size = containers.size();
    for ( auto&& bag : bags )
    {
        if ( bag.contains.count(containee) )
        {
            containers.insert(bag.adj);
        }
    }
    return 0;
}

class bag_parser
{
public:
    bag_parser(){}
    void parse_bags(std::istream& is)
    {
        static const boost::regex pattern("^([a-z ]*) bags contain (.*)\\.$");
        static const boost::regex contained("([\\d]) ([a-z ]*) bags?");
        static const std::string contained_delim = ", ";

        for ( std::string line; std::getline(is, line); )
        {
            struct bag result;
            boost::smatch groups;
            if ( boost::regex_search(line, groups, pattern) )
            {
                result.adj = groups[1];
                if ( groups[2] == "no other bags")
                {
                    bags_.emplace_back(result);
                    continue;
                }
                auto contained_begin = groups[2].begin();
                auto contained_end = std::search(contained_begin, groups[2].end(), contained_delim.begin(), contained_delim.end());
                boost::smatch contained_groups;
                do
                {
                    if ( boost::regex_search(contained_begin, contained_end, contained_groups, contained) )
                    {
                        result.contains[contained_groups[2]] = boost::lexical_cast<int>(contained_groups[1]);
                        contained_in_[contained_groups[2]].insert(result.adj);
                    }
                    if ( contained_end != groups[2].end() )
                    {
                        contained_begin = contained_end + contained_delim.size();
                        contained_end = std::search(contained_begin, groups[2].end(), contained_delim.begin(), contained_delim.end());
                    }
                    else
                    {
                        contained_begin = contained_end;
                    }
                } while ( contained_begin != groups[2].end() );
                bags_.emplace_back(result);
                continue;
            }
            throw 42;
        }
    }
    int count_bags_could_contain(const std::string& containee)
    {
        std::set<std::string> containers;
        std::deque<std::string> to_check = { containee };
        while ( to_check.size() > 0 )
        {
            std::string checking = to_check.front(); to_check.pop_front();
            for ( auto&& container : contained_in_[checking] )
            {
                if ( containers.insert(container).second )
                {
                    to_check.push_back(container);
                }
            }
        }
        return containers.size();
    }
private:
    std::vector<bag> bags_;
    std::map<std::string, std::set<std::string> > contained_in_;
};

int main()
{
    std::ifstream inf(PROJEUL_AOC_PATH "/07_input.txt");

    bag_parser bp;
    bp.parse_bags(inf);
    auto result = bp.count_bags_could_contain("shiny gold");
    std::cout << "result: " << result << std::endl;
    return 0;
}
