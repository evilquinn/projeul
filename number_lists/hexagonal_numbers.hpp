/*
 * hexagonal_numbers.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef HEXAGONAL_NUMBERS_HPP_
#define HEXAGONAL_NUMBERS_HPP_

#include <stddef.h>
#include <vector>

class hexagonal_numbers
{
public:
    hexagonal_numbers(size_t num);
    virtual ~hexagonal_numbers();

    void print();
    bool is_hexagonal(size_t n);
    size_t get_term(size_t n);
    static size_t calc_hexagonal_number_for_term(size_t n);

private:
    void calc_hexagonal_numbers();

    size_t   num_;
    std::vector<size_t> hexagonals_;
    size_t max_;
};

#endif /* HEXAGONAL_NUMBERS_HPP_ */
