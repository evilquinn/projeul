/*
 * pe34.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE34_HPP_
#define PE34_HPP_

#include "pe.hpp"

class pe34 : public pe
{
public:
    pe34() : name_( "pe34" ){};
    ~pe34() override = default;
    std::string& name() override;
    int          number() override { return 34; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE34_HPP_ */
