/*
 * pe29.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE29_HPP_
#define PE29_HPP_

#include <prime_sieve.hpp>
#include "pe.hpp"

class pe29 : public pe
{
public:
    pe29() : name_( "pe29" ){};
    ~pe29() override = default;
    std::string& name() override;
    int number() override { return 29; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE29_HPP_ */
