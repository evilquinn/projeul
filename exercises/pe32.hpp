/*
 * pe32.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE32_HPP_
#define PE32_HPP_

#include "pe.hpp"

class pe32 : public pe
{
public:
    pe32() : name_( "pe32" ){};
    ~pe32() override = default;
    std::string& name() override;
    int          number() override { return 32; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE32_HPP_ */
