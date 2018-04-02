/*
 * pe52.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE52_HPP_
#define PE52_HPP_

#include "pe.hpp"

class pe52 : public pe
{
public:
    pe52() : name_( "pe52" ){};
    ~pe52() override = default;
    std::string& name() override;
    int          number() override { return 52; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE52_HPP_ */
