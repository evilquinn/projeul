
#include <iostream>
#include "pe_register.hpp"

#include "pe27.hpp"
#include "pe29.hpp"
#include "pe30.hpp"
#include "pe31.hpp"
#include "pe32.hpp"
#include "pe33.hpp"
#include "pe34.hpp"
#include "pe35.hpp"
#include "pe36.hpp"
#include "pe37.hpp"
#include "pe38.hpp"
#include "pe39.hpp"
#include "pe40.hpp"
#include "pe41.hpp"
#include "pe42.hpp"
#include "pe43.hpp"
#include "pe44.hpp"
#include "pe45.hpp"
#include "pe46.hpp"
#include "pe47.hpp"
#include "pe48.hpp"
#include "pe49.hpp"
#include "pe50.hpp"
#include "pe51.hpp"
#include "pe52.hpp"
#include "pe53.hpp"
#include "pe54.hpp"
#include "pe55.hpp"
#include "pe56.hpp"
#include "pe57.hpp"
#include "pe58.hpp"
#include "pe59.hpp"
#include "pe60.hpp"
#include "pe61.hpp"
#include "pe62.hpp"
#include "pe63.hpp"
#include "pe64.hpp"
#include "pe65.hpp"
#include "pe66.hpp"
#include "pe67.hpp"

pe_register::pe_register() :
    reg_()
{
    reg(std::unique_ptr<pe>(new pe27()));
    reg(std::unique_ptr<pe>(new pe29()));
    reg(std::unique_ptr<pe>(new pe30()));
    reg(std::unique_ptr<pe>(new pe31()));
    reg(std::unique_ptr<pe>(new pe32()));
    reg(std::unique_ptr<pe>(new pe33()));
    reg(std::unique_ptr<pe>(new pe34()));
    reg(std::unique_ptr<pe>(new pe35()));
    reg(std::unique_ptr<pe>(new pe36()));
    reg(std::unique_ptr<pe>(new pe37()));
    reg(std::unique_ptr<pe>(new pe38()));
    reg(std::unique_ptr<pe>(new pe39()));
    reg(std::unique_ptr<pe>(new pe40()));
    reg(std::unique_ptr<pe>(new pe41()));
    reg(std::unique_ptr<pe>(new pe42()));
    reg(std::unique_ptr<pe>(new pe43()));
    reg(std::unique_ptr<pe>(new pe44()));
    reg(std::unique_ptr<pe>(new pe45()));
    reg(std::unique_ptr<pe>(new pe46()));
    reg(std::unique_ptr<pe>(new pe47()));
    reg(std::unique_ptr<pe>(new pe48()));
    reg(std::unique_ptr<pe>(new pe49()));
    reg(std::unique_ptr<pe>(new pe50()));
    reg(std::unique_ptr<pe>(new pe51()));
    reg(std::unique_ptr<pe>(new pe52()));
    reg(std::unique_ptr<pe>(new pe53()));
    reg(std::unique_ptr<pe>(new pe54()));
    reg(std::unique_ptr<pe>(new pe55()));
    reg(std::unique_ptr<pe>(new pe56()));
    reg(std::unique_ptr<pe>(new pe57()));
    reg(std::unique_ptr<pe>(new pe58()));
    reg(std::unique_ptr<pe>(new pe59()));
    reg(std::unique_ptr<pe>(new pe60()));
    reg(std::unique_ptr<pe>(new pe61()));
    reg(std::unique_ptr<pe>(new pe62()));
    reg(std::unique_ptr<pe>(new pe63()));
    reg(std::unique_ptr<pe>(new pe64()));
    reg(std::unique_ptr<pe>(new pe65()));
    reg(std::unique_ptr<pe>(new pe66()));
    reg(std::unique_ptr<pe>(new pe67()));
};

void pe_register::reg(std::unique_ptr<pe> ex)
{
    reg_.insert(std::make_pair(ex->number(), std::move(ex)));
}

void pe_register::run(int ex)
{
    if ( ex == 0 )
    {
        ex = reg_.rbegin()->first;
    }
    std::cout << "Exercise " << ex << std::endl;
    reg_.at(ex)->run();
}
