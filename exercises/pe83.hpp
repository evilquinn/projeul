/*
 * pe83.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE83_HPP_
#define PE83_HPP_

#include <pe.hpp>
#include <pe_register.hpp>

class pe83 : public pe
{
public:
    pe83() : name_( "pe83" ) {};
    ~pe83() override = default;
    std::string& name() override;
    int          number() override { return 83; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE83_HPP_ */
