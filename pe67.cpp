/*
 * pe67.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe67.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>


std::string& pe67::name()
{
    return name_;
}

void pe67::run()
{
    /*
     * By starting at the top of the triangle below and moving to adjacent
     * numbers on the row below, the maximum total from top to bottom is 23.
     *
     *      3
     *     7 4
     *    2 4 6
     *   8 5 9 3
     *
     * That is, 3 + 7 + 4 + 9 = 23.
     *
     * Find the maximum total from top to bottom in triangle.txt
     * (right click and 'Save Link/Target As...'), a 15K text file containing
     * a triangle with one-hundred rows.
     */

    std::ifstream data_file;
    data_file.open("../data/pe67_triangle.txt");

    typedef std::vector<std::vector<size_t>> triangle_type;
    triangle_type tri;

    boost::char_separator<char> space_sep(" ");
    std::string line;
    while ( std::getline(data_file, line) )
    {
        boost::tokenizer< boost::char_separator<char> > nums(line,
                                                             space_sep);
        std::vector<size_t> newline;
        BOOST_FOREACH (const std::string& numstring, nums)
        {
            size_t num = stoi(numstring);
            newline.push_back(num);
        }
        tri.push_back(newline);
    }


    BOOST_FOREACH (const std::vector<size_t>& line, tri)
    {
        BOOST_FOREACH (size_t num, line)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    size_t result = 0;

    std::cout << "result : " << result << std::endl;
}
