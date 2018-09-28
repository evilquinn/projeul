/*
 * pe48.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE48_HPP_
#define PE48_HPP_

#include "pe.hpp"

class pe48 : public pe
{
public:
    pe48() : name_( "pe48" ){};
    ~pe48() override = default;
    std::string& name() override;
    int number() override { return 48; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE48_HPP_ */
