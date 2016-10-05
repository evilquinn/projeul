/*
 * polygonal_numbers.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef POLYGONAL_NUMBERS_HPP_
#define POLYGONAL_NUMBERS_HPP_

#include <stddef.h>
#include <set>
#include <vector>

typedef size_t (*function_of_n)(size_t n);

class polygonal_numbers
{
public:
    polygonal_numbers(size_t num, function_of_n func);
    virtual ~polygonal_numbers();

    void print();
    bool is_in(size_t n);
    size_t get_term(size_t n);
    static size_t triangle(size_t n);
    static size_t square(size_t n);
    static size_t pentagonal(size_t n);
    static size_t hexagonal(size_t n);
    static size_t heptagonal(size_t n);
    static size_t octagonal(size_t n);

private:
    void calc_polygonal_numbers();

    size_t   num_;
    function_of_n       number_func_;
    std::vector<size_t> numbers_;
};

#endif /* POLYGONAL_NUMBERS_HPP_ */
