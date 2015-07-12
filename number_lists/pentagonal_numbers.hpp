/*
 * pentagonal_numbers.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef PENTAGONAL_NUMBERS_HPP_
#define PENTAGONAL_NUMBERS_HPP_

#include <stddef.h>
#include <set>

class pentagonal_numbers
{
public:
    pentagonal_numbers(size_t num);
    virtual ~pentagonal_numbers();

    void print();
    bool is_pentagonal(size_t n);
    size_t get_term(size_t n);
    static size_t calc_pentagonal_number_for_term(size_t n);

private:
    void calc_pentagonal_numbers();

    size_t   num_;
    std::set<size_t> pentagonals_;
    size_t max_;
};

#endif /* PENTAGONAL_NUMBERS_HPP_ */
