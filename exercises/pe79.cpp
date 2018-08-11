/*
 * pe79.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <pe79.hpp>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <utils.hpp>

namespace { // anonymous

template<typename Value>
struct digit_guy
{
    Value val;
    std::set<Value> lefts;
    std::set<Value> rights;
};

} // end namespace anonymous

std::string& pe79::name() { return name_; }
void         pe79::run()
{
    /*
     * A common security method used for online banking is to ask the
     * user for three random characters from a passcode. For example,
     * if the passcode was 531278, they may ask for the 2nd, 3rd, and 5th
     * characters; the expected reply would be: 317.
     *
     * The text file, keylog.txt, contains fifty successful login attempts.
     *
     * Given that the three characters are always asked for in order,
     * analyse the file so as to determine the shortest possible secret
     * passcode of unknown length.
     *
     *
     */

    std::ifstream data_file;
    data_file.open( "/home/evilquinn/git/projeul/data/pe79_keylog.txt" );

    std::map<int, struct digit_guy<int> > attempts;
    std::string line;
    while ( std::getline(data_file, line ) )
    {
        for ( size_t i = 0; i < line.size(); ++i )
        {
            int digit = line[i] - '0';
            auto curr = attempts[digit];
            curr.val = digit;
            for ( size_t l = 0; l < i; ++l )
            {
                curr.lefts.insert(line[l]-'0');
            }
            for ( size_t r = i+1; r < line.size(); ++r )
            {
                curr.rights.insert(line[r]-'0');
            }
            attempts[digit] = curr;
        }
    }

    for ( auto e : attempts )
    {
        for ( auto l : e.second.lefts )
        {
            std::cout << l << ", ";
        }
        std::cout << "| " << e.second.val << " |, ";
        for ( auto r : e.second.rights )
        {
            std::cout << r << ", ";
        }
        std::cout << std::endl;
    }
}
