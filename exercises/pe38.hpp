/*
 * pe38.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE38_HPP_
#define PE38_HPP_

#include "pe.hpp"

class pe38 : public pe
{
public:
    pe38() : name_( "pe38" ){};
    ~pe38() override = default;
    std::string& name() override;
    int number() override { return 38; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE38_HPP_ */
