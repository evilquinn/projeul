/*
 * pe56.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE56_HPP_
#define PE56_HPP_

#include "pe.hpp"

class pe56 : public pe
{
public:
    pe56() : name_( "pe56" ){};
    ~pe56() override = default;
    std::string& name() override;
    int          number() override { return 56; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE56_HPP_ */
