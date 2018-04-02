/*
 * pe53.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE53_HPP_
#define PE53_HPP_

#include "pe.hpp"

class pe53 : public pe
{
public:
    pe53() : name_( "pe53" ){};
    ~pe53() override = default;
    std::string& name() override;
    int          number() override { return 53; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE53_HPP_ */
