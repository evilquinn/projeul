/*
 * pe42.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE42_HPP_
#define PE42_HPP_

#include "pe.hpp"
#include <triangle_numbers/triangle_numbers.hpp>


class pe42 : public pe
{
public:
    pe42() :
        tris_(1000),
        name_("pe42")
    {};
    virtual ~pe42()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    triangle_numbers tris_;
    std::string name_;
};

#endif /* PE42_HPP_ */
