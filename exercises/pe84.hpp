/*
 * pe84.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE84_HPP_
#define PE84_HPP_

#include <pe.hpp>
#include <pe_register.hpp>

class pe84 : public pe
{
public:
    pe84() : name_( "pe84" ){};
    ~pe84() override = default;
    std::string& name() override;
    int number() override { return 84; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE84_HPP_ */
