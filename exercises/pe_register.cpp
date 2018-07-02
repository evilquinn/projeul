
#include <iostream>
#include <pe_register.hpp>

#include <pe27.hpp>
#include <pe29.hpp>
#include <pe30.hpp>
#include <pe31.hpp>
#include <pe32.hpp>
#include <pe33.hpp>
#include <pe34.hpp>
#include <pe35.hpp>
#include <pe36.hpp>
#include <pe37.hpp>
#include <pe38.hpp>
#include <pe39.hpp>
#include <pe40.hpp>
#include <pe41.hpp>
#include <pe42.hpp>
#include <pe43.hpp>
#include <pe44.hpp>
#include <pe45.hpp>
#include <pe46.hpp>
#include <pe47.hpp>
#include <pe48.hpp>
#include <pe49.hpp>
#include <pe50.hpp>
#include <pe51.hpp>
#include <pe52.hpp>
#include <pe53.hpp>
#include <pe54.hpp>
#include <pe55.hpp>
#include <pe56.hpp>
#include <pe57.hpp>
#include <pe58.hpp>
#include <pe59.hpp>
#include <pe60.hpp>
#include <pe61.hpp>
#include <pe62.hpp>
#include <pe63.hpp>
#include <pe64.hpp>
#include <pe65.hpp>
#include <pe66.hpp>
#include <pe67.hpp>
#include <pe68.hpp>
#include <pe69.hpp>
#include <pe70.hpp>
#include <pe71.hpp>
#include <pe72.hpp>

pe_register::pe_register() : reg_()
{
    reg( std::make_unique<pe27>() );
    reg( std::make_unique<pe29>() );
    reg( std::make_unique<pe30>() );
    reg( std::make_unique<pe31>() );
    reg( std::make_unique<pe32>() );
    reg( std::make_unique<pe33>() );
    reg( std::make_unique<pe34>() );
    reg( std::make_unique<pe35>() );
    reg( std::make_unique<pe36>() );
    reg( std::make_unique<pe37>() );
    reg( std::make_unique<pe38>() );
    reg( std::make_unique<pe39>() );
    reg( std::make_unique<pe40>() );
    reg( std::make_unique<pe41>() );
    reg( std::make_unique<pe42>() );
    reg( std::make_unique<pe43>() );
    reg( std::make_unique<pe44>() );
    reg( std::make_unique<pe45>() );
    reg( std::make_unique<pe46>() );
    reg( std::make_unique<pe47>() );
    reg( std::make_unique<pe48>() );
    reg( std::make_unique<pe49>() );
    reg( std::make_unique<pe50>() );
    reg( std::make_unique<pe51>() );
    reg( std::make_unique<pe52>() );
    reg( std::make_unique<pe53>() );
    reg( std::make_unique<pe54>() );
    reg( std::make_unique<pe55>() );
    reg( std::make_unique<pe56>() );
    reg( std::make_unique<pe57>() );
    reg( std::make_unique<pe58>() );
    reg( std::make_unique<pe59>() );
    reg( std::make_unique<pe60>() );
    reg( std::make_unique<pe61>() );
    reg( std::make_unique<pe62>() );
    reg( std::make_unique<pe63>() );
    reg( std::make_unique<pe64>() );
    reg( std::make_unique<pe65>() );
    reg( std::make_unique<pe66>() );
    reg( std::make_unique<pe67>() );
    reg( std::make_unique<pe68>() );
    reg( std::make_unique<pe69>() );
    reg( std::make_unique<pe70>() );
    reg( std::make_unique<pe71>() );
    reg( std::make_unique<pe72>() );
};

void pe_register::reg( std::unique_ptr<pe> ex )
{
    reg_.insert( std::make_pair( ex->number(), std::move( ex ) ) );
}

void pe_register::run( int ex )
{
    if ( ex == 0 )
    {
        ex = reg_.rbegin()->first;
    }
    std::cout << "Exercise " << ex << std::endl;
    reg_.at( ex )->run();
}
