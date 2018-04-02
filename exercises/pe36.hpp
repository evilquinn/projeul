/*
 * pe36.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE36_HPP_
#define PE36_HPP_

#include "pe.hpp"

class pe36 : public pe
{
public:
    pe36() : name_( "pe36" ){};
    ~pe36() override = default;
    std::string& name() override;
    int          number() override { return 36; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE36_HPP_ */
