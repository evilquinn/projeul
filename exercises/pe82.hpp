/*
 * pe82.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE82_HPP_
#define PE82_HPP_

#include <pe.hpp>
#include <pe_register.hpp>

class pe82 : public pe
{
public:
    pe82() : name_( "pe82" ) {};
    ~pe82() override = default;
    std::string& name() override;
    int          number() override { return 82; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE82_HPP_ */
