/*
 * pe43.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE43_HPP_
#define PE43_HPP_

#include "pe.hpp"

class pe43 : public pe
{
public:
    pe43() : name_( "pe43" ){};
    ~pe43() override = default;
    std::string& name() override;
    int number() override { return 43; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE43_HPP_ */
