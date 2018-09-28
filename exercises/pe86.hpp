/*
 * pe86.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE86_HPP_
#define PE86_HPP_

#include <pe.hpp>
#include <pe_register.hpp>

class pe86 : public pe
{
public:
    pe86() : name_( "pe86" ){};
    ~pe86() override = default;
    std::string& name() override;
    int number() override { return 86; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE86_HPP_ */
