/*
 * pe45.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE45_HPP_
#define PE45_HPP_

#include <hexagonal_numbers.hpp>
#include <pentagonal_numbers.hpp>
#include <triangle_numbers.hpp>
#include "pe.hpp"

#define PE45_NUM_PENTS 1000000
#define PE45_NUM_TRIS 1000000
#define PE45_NUM_HEXS 1000000

class pe45 : public pe
{
public:
    pe45() : name_( "pe45" ){};
    ~pe45() override = default;
    std::string& name() override;
    int          number() override { return 45; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE45_HPP_ */
