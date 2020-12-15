/*
 * https://adventofcode.com/2020/day/13
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include <aoc/path_def.hpp>

class wait_on_bus
{
public:
    wait_on_bus(std::istream& is)
    {
        parse_input(is);
    }
    void parse_input(std::istream& is)
    {
        std::string line;
        if ( std::getline(is, line) )
        {
            avail_from_ = boost::lexical_cast<size_t>(line);
        }
        else throw std::runtime_error("failed to parse avail_from_ from input");
        if ( std::getline(is, line) )
        {
            std::vector<std::string> columns;
            boost::split(columns, line, boost::is_any_of(","));
            for ( auto&& col : columns )
            {
                if ( col == "x" ) continue; // not in service
                bus_ids_.push_back(boost::lexical_cast<size_t>(col));
            }
        }
    }
    size_t calc_result()
    {
        std::vector<size_t> first_departs_after;
        for ( auto&& bus_id : bus_ids_ )
        {
            size_t bus_departs = 0;
            while ( bus_departs < avail_from_ )
            {
                bus_departs += bus_id;
            }
            first_departs_after.push_back(bus_departs);
        }
        size_t earliest = std::numeric_limits<size_t>::max();
        size_t earliest_bus_id = 0;
        for ( size_t i = 0; i < first_departs_after.size(); ++i )
        {
            if ( earliest > first_departs_after[i] )
            {
                earliest = first_departs_after[i];
                earliest_bus_id = bus_ids_[i];
            }
        }
        return ( earliest - avail_from_ ) * earliest_bus_id;
    }
private:
    size_t avail_from_;
    std::vector<size_t> bus_ids_;
};

int main()
{
#if 0
    std::vector<std::string> data = {
    };
    for ( auto&& datum : data )
    {
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/13_input.txt");
    wait_on_bus waity(inf);
    auto result = waity.calc_result();
    std::cout << "result: " << result << std::endl;
#endif
    return 0;
}
