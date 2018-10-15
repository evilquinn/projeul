/*
 * pe89.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include <iostream>
#include <fstream>
#include <pe89.hpp>

namespace {  // anonymous

}  // namespace anonymous

std::string& pe89::name() { return name_; }
void pe89::run()
{
    std::ifstream data_file;
    data_file.open( "/home/evilquinn/git/projeul/data/pe89_roman.txt" );

    std::string line;
    size_t bytes = 0;
    size_t saved = 0;
    while ( std::getline( data_file, line ) )
    {
        bytes += line.length();
        std::cout << line << "\n";

        char saw = '0';
        size_t seen = 0;
        bool half = false;

        for ( size_t i = line.length() - 1;
              i < line.length();
              --i )
        {
            if ( line[i] == 'M' )
            {
                break;
            }
            if ( line[i] == saw )
            {
                ++seen;
                if ( seen == 4)
                {
                    seen = 0;
                    saved += 2;
                    half = true;
                }

            }
            else
            {
                if ( half )
                {
                    if ( line[i] == 'V' && saw == 'I' ||
                         line[i] == 'L' && saw == 'X' ||
                         line[i] == 'D' && saw == 'C' )
                    {
                        ++saved;
                    }
                    half = false;
                }
                saw = line[i];
                seen = 1;
            }
        }
    }

    std::cout << "bytes: " << bytes << std::endl;
    std::cout << "saved: " << saved << std::endl;
}

/*
 * For a number written in Roman numerals to be considered valid there
 * are basic rules which must be followed. Even though the rules allow
 * some numbers to be expressed in more than one way there is always a
 * "best" way of writing a particular number.
 *
 * For example, it would appear that there are at least six ways of
 * writing the number sixteen:
 *
 *   IIIIIIIIIIIIIIII
 *   VIIIIIIIIIII
 *   VVIIIIII
 *   XIIIIII
 *   VVVI
 *   XVI
 *
 * However, according to the rules only XIIIIII and XVI are valid, and the
 * last example is considered to be the most efficient, as it uses the
 * least number of numerals.
 *
 * The 11K text file, pe86_roman.txt, contains one thousand numbers written
 * in valid, but not necessarily minimal, Roman numerals; see About...
 * Roman Numerals for the definitive rules for this problem.
 *
 * Find the number of characters saved by writing each of these in their
 * minimal form.
 *
 * Note: You can assume that all the Roman numerals in the file contain no
 * more than four consecutive identical units.
 *
 */
