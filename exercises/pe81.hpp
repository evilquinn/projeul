/*
 * pe81.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE81_HPP_
#define PE81_HPP_

#include <pe.hpp>
#include <pe_register.hpp>

class pe81 : public pe
{
public:
    pe81() : name_( "pe81" ) {};
    ~pe81() override = default;
    std::string& name() override;
    int          number() override { return 81; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE81_HPP_ */
