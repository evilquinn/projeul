/*
 * pe69.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE69_HPP_
#define PE69_HPP_

#include "pe.hpp"

class pe69 : public pe
{
public:
    pe69() : name_( "pe69" ){};
    ~pe69() override = default;
    std::string& name() override;
    int number() override { return 69; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE69_HPP_ */
