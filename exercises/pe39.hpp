/*
 * pe39.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE39_HPP_
#define PE39_HPP_

#include "pe.hpp"

class pe39 : public pe
{
public:
    pe39() : name_( "pe39" ){};
    ~pe39() override = default;
    std::string& name() override;
    int number() override { return 39; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE39_HPP_ */
