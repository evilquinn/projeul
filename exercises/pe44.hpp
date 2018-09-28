/*
 * pe44.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE44_HPP_
#define PE44_HPP_

#include <pentagonal_numbers.hpp>
#include "pe.hpp"

#define PE44_NUM_PENTS 1000000

class pe44 : public pe
{
public:
    pe44() : name_( "pe44" ){};
    ~pe44() override = default;
    std::string& name() override;
    int number() override { return 44; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE44_HPP_ */
