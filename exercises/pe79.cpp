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
    data_file.open( "../data/pe79_keylog.txt" );

    std::vector<int> attempt;
    std::string line;
    while ( std::getline(data_file, line ) )
    {
        for ( size_t i = 0; i < line.size(); ++i )
        {
            if ( std::find(line.begin(), line.end(), '3') != line.end() )
            {
                std::cout << "line has 3! " << line << std::endl;
            }
        }
    }
    std::cout << std::endl;
}
