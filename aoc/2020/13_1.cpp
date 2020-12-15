/*
 * https://adventofcode.com/2020/day/13
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

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
            for ( size_t i = 0; i < columns.size(); ++i )
            {
                if ( columns[i] == "x" ) continue; // not in service
                bus_ids_idx_[boost::lexical_cast<size_t>(columns[i])] = i;
            }
        }
    }
    size_t calc_result()
    {
        std::map<size_t, size_t> first_departs_after;
        for ( auto&& bus_id : bus_ids_idx_ )
        {
            size_t bus_departs = 0;
            while ( bus_departs < avail_from_ )
            {
                bus_departs += bus_id.first;
            }
            first_departs_after[bus_id.first] = bus_departs;
        }
        size_t earliest = std::numeric_limits<size_t>::max();
        size_t earliest_bus_id = 0;
        for ( auto&& departure : first_departs_after )
        {
            if ( earliest > departure.second )
            {
                earliest = departure.second;
                earliest_bus_id = departure.first;
            }
        }
        return ( earliest - avail_from_ ) * earliest_bus_id;
    }
    size_t calc_result_2()
    {
        auto biggest_bus_id = bus_ids_idx_.rbegin();
        size_t t_cand = biggest_bus_id->first - biggest_bus_id->second;
        bool success = false;
        while ( !success )
        {
            success = true;
            for ( auto&& bus_id : bus_ids_idx_ )
            {
                if ( ( ( t_cand + bus_id.second ) % bus_id.first ) != 0 )
                {
                    success = false;
                    t_cand += biggest_bus_id->first;
                    break;
                }
            }
        }
        return t_cand;
    }
private:
    size_t avail_from_;
    std::map<size_t, size_t> bus_ids_idx_;
};

int main()
{
#if 1
    std::vector<std::string> data = {
        "1\n7,13,x,x,59,x,31,19"
    };
    for ( auto&& datum : data )
    {
        std::istringstream iss(datum);
        wait_on_bus waity(iss);
        auto result = waity.calc_result_2();
        std::cout << "result: " << result << std::endl;
    }
#endif
#if 1
    std::ifstream inf(PROJEUL_AOC_PATH "/13_input.txt");
    wait_on_bus waity(inf);
    auto result = waity.calc_result_2();
    std::cout << "result: " << result << std::endl;
#endif
    return 0;
}
