/*
 * pe71.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE71_HPP_
#define PE71_HPP_

#include "pe.hpp"

class pe71 : public pe
{
public:
    pe71() : name_( "pe71" ){};
    ~pe71() override = default;
    std::string& name() override;
    int number() override { return 71; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE71_HPP_ */
