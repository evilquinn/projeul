#include <boost/program_options.hpp>
#include <iostream>

#include "pe_register.hpp"
#include "utils.hpp"

namespace po = boost::program_options;

#define RUN_EX( ex_num ) RUN_EX_CONCAT( ex_num )
#define RUN_EX_CONCAT( ex_num ) \
    do                          \
    {                           \
        pe##ex_num ex;          \
        ex.run();               \
    } while ( 0 )

int main( int argc, char* argv[] )
{
    // Declare the supported options.
    po::options_description desc( "Options" );
    desc.add_options()( "help,h", "produce help message" )(
        "exercise,e",
        po::value<int>()->default_value( 0 ),
        "exercise to run" );

    po::variables_map vm;
    try
    {
        po::store( po::parse_command_line( argc, argv, desc ), vm );
    }
    catch ( const po::invalid_command_line_syntax& exception )
    {
        std::cout << "Failed to parse command line: " << exception.what()
                  << std::endl
                  << desc << std::endl;
        return 1;
    }
    po::notify( vm );

    if ( vm.count( "help" ) > 0 )
    {
        std::cout << desc << "\n";
        return 1;
    }

    int         exercise = vm["exercise"].as<int>();
    pe_register pe_reg;
    try
    {
        pe_reg.run( exercise );
    }
    catch ( const std::out_of_range& )
    {
        std::cout << "Exercise " << exercise << " isn't registered"
                  << std::endl;
        return 1;
    }

    return 0;
}
