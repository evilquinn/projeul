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
    pe62() :
        name_("pe62")
    {};
    virtual ~pe62()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    std::string name_;
};

#endif /* PE62_HPP_ */
