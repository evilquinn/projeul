/*
 * pe42.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE42_HPP_
#define PE42_HPP_

#include <triangle_numbers.hpp>
#include "pe.hpp"

class pe42 : public pe
{
public:
    pe42() : name_( "pe42" ){};
    ~pe42() override = default;
    std::string& name() override;
    int          number() override { return 42; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE42_HPP_ */
