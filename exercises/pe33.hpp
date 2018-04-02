/*
 * pe33.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE33_HPP_
#define PE33_HPP_

#include "pe.hpp"

class pe33 : public pe
{
public:
    pe33() : name_( "pe33" ){};
    ~pe33() override = default;
    std::string& name() override;
    int          number() override { return 33; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE33_HPP_ */
