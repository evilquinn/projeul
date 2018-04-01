/*
 * triangle_numbers.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef TRIANGLE_NUMBERS_HPP_
#define TRIANGLE_NUMBERS_HPP_

#include <stddef.h>
#include <set>
#include <vector>

class triangle_numbers
{
public:
    explicit triangle_numbers( size_t num );
    virtual ~triangle_numbers();

    void print();
    bool is_triangle( size_t n );
    size_t get_term( size_t n );
    static size_t calc_triangle_number_for_term( size_t n );

private:
    void calc_triangle_numbers();

    size_t              num_;
    std::vector<size_t> triangles_;
};

#endif /* TRIANGLE_NUMBERS_HPP_ */
