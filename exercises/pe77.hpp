/*
 * pe77.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE77_HPP_
#define PE77_HPP_

#include "pe.hpp"

class pe77 : public pe
{
public:
    pe77() : name_( "pe77" ){};
    ~pe77() override = default;
    std::string& name() override;
    int          number() override { return 77; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE77_HPP_ */
