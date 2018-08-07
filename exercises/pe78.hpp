/*
 * pe78.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE78_HPP_
#define PE78_HPP_

#include "pe.hpp"

class pe78 : public pe
{
public:
    pe78() : name_( "pe78" ){};
    ~pe78() override = default;
    std::string& name() override;
    int          number() override { return 78; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE78_HPP_ */
