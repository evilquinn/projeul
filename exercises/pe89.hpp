/*
 * pe89.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE89_HPP_
#define PE89_HPP_

#include <pe.hpp>
#include <pe_register.hpp>

class pe89 : public pe
{
public:
    pe89() : name_( "pe89" ){};
    ~pe89() override = default;
    std::string& name() override;
    int number() override { return 89; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE89_HPP_ */
