/*
 * pe59.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE59_HPP_
#define PE59_HPP_

#include "pe.hpp"

class pe59 : public pe
{
public:
    pe59() : name_( "pe59" ){};
    ~pe59() override = default;
    std::string& name() override;
    int number() override { return 59; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE59_HPP_ */
