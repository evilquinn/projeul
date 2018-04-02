/*
 * pe62.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE62_HPP_
#define PE62_HPP_

#include "pe.hpp"

class pe62 : public pe
{
public:
    pe62() : name_( "pe62" ){};
    ~pe62() override = default;
    std::string& name() override;
    int          number() override { return 62; }
    void         run() override;

private:
    std::string name_;
};

#endif /* PE62_HPP_ */
