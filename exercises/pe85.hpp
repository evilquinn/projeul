/*
 * pe85.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE85_HPP_
#define PE85_HPP_

#include <pe.hpp>
#include <pe_register.hpp>

class pe85 : public pe
{
public:
    pe85() : name_( "pe85" ){};
    ~pe85() override = default;
    std::string& name() override;
    int number() override { return 85; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE85_HPP_ */
