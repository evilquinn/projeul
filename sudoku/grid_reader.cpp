
#include <iostream>
#include <fstream>
#include <string>
#include <sudoku/grid_reader.hpp>

evilquinn::sudoku::grid_reader::grid_reader( const std::string& file ) :
    input_owner_( std::make_unique<std::ifstream>(file) ),
    input_(*input_owner_)
{
    if ( !input_ )
    {
        throw input_error( "failed to open file: " + file );
    }
}
evilquinn::sudoku::grid_reader::grid_reader(std::istringstream iss) :
    input_owner_( std::make_unique<std::istringstream>(std::move(iss))),
    input_(*input_owner_)
{
    if ( !input_ )
    {
        throw input_error( "failed to read string: " + iss.str() );
    }
}

boost::optional<evilquinn::sudoku::grid>
evilquinn::sudoku::grid_reader::getgrid()
{
    std::string line;
    if ( !std::getline( input_, line ) )
    {
        return boost::optional<grid>{};
    }

    //std::cout << "reading: " << line << std::endl;
    auto first_line_cache = input_.tellg();

    // get first line, determine length, and ass-u-me it's a square
    if ( !std::getline( input_, line ) )
    {
        throw grid_read_error(
            "couldn't read first grid line to determine grid dimensions" );
    }

    // and put it back to make the next loop easier (!)
    input_.seekg( first_line_cache );

    const size_t dim_x = line.size();
    grid current( { dim_x, dim_x } );

    for ( size_t y = 0; y < dim_x; ++y )
    {
        if ( !std::getline( input_, line ) )
        {
            throw grid_read_error(
                "couldn't read line during grid assigment" );
        }
        for ( size_t x = 0; x < dim_x; ++x )
        {
            current.at( { x, y } ).set( line[x] - '0' );
        }
    }
    return current;
}
