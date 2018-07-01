/*
 * pe70.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE70_HPP_
#define PE70_HPP_

#include "pe.hpp"

class pe70 : public pe
{
public:
    pe70() : name_( "pe70" ){};
    ~pe70() override = default;
    std::string& name() override;
    int          number() override { return 70; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE70_HPP_ */
