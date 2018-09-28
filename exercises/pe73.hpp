/*
 * pe73.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE73_HPP_
#define PE73_HPP_

#include "pe.hpp"

class pe73 : public pe
{
public:
    pe73() : name_( "pe73" ){};
    ~pe73() override = default;
    std::string& name() override;
    int number() override { return 73; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE73_HPP_ */
