/*
 * pe67.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE67_HPP_
#define PE67_HPP_

#include "pe.hpp"

class pe67 : public pe
{
public:
    pe67() : name_( "pe67" ){};
    ~pe67() override = default;
    std::string& name() override;
    int number() override { return 67; }
    void run() override;

private:
    std::string name_;
};

#endif /* PE67_HPP_ */
