/*
 * pe72.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE72_HPP_
#define PE72_HPP_

#include "pe.hpp"

class pe72 : public pe
{
public:
    pe72() : name_( "pe72" ){};
    ~pe72() override = default;
    std::string& name() override;
    int number() override { return 72; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE72_HPP_ */
