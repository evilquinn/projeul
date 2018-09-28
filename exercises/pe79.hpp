/*
 * pe79.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE79_HPP_
#define PE79_HPP_

#include "pe.hpp"

class pe79 : public pe
{
public:
    pe79() : name_( "pe79" ){};
    ~pe79() override = default;
    std::string& name() override;
    int number() override { return 79; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE79_HPP_ */
