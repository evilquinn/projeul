/*
 * gint.hpp
 *
 *  Created on: 16 Jun 2015
 *      Author: evilquinn
 */

#ifndef GINT_HPP_
#define GINT_HPP_

#include <stddef.h>
#include <stdint.h>
#include <deque>

class gint
{
public:
    gint();
    gint(size_t n);
    virtual ~gint();

    void print();

private:

    std::deque<uint8_t> n_;
};

#endif /* GINT_HPP_ */
