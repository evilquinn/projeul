/*
 * pe45.h
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#ifndef PE45_HPP_
#define PE45_HPP_

#include "pe.hpp"
#include <pentagonal_numbers.hpp>
#include <triangle_numbers.hpp>
#include <hexagonal_numbers.hpp>

#define PE45_NUM_PENTS 1000000
#define PE45_NUM_TRIS  1000000
#define PE45_NUM_HEXS  1000000

class pe45 : public pe
{
public:
    pe45() :
        pents_(PE45_NUM_PENTS),
        tris_(PE45_NUM_TRIS),
        hexs_(PE45_NUM_HEXS),
        name_("pe45")
    {};
    virtual ~pe45()
    {
    };
    virtual std::string& name();
    virtual void run();
private:
    pentagonal_numbers pents_;
    triangle_numbers   tris_;
    hexagonal_numbers  hexs_;
    std::string name_;
};

#endif /* PE45_HPP_ */
