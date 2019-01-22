
#include <sudoku/grid_reader.hpp>
#include <string>
#include <iostream>

evilquinn::sudoku::grid_reader::grid_reader(const std::string& file) :
    file_(file)
{
    if ( !file_ )
    {
        throw file_error("failed to open file");
    }
}

boost::optional<evilquinn::sudoku::grid>
evilquinn::sudoku::grid_reader::getgrid()
{
    std::string line;
    if ( !std::getline(file_, line) )
    {
        return boost::optional<grid>{};
    }

    std::cout << "reading: " << line << std::endl;
    auto first_line_cache = file_.tellg();

    // get first line, determine length, and ass-u-me it's a square
    if ( !std::getline(file_, line) )
    {
        throw grid_read_error("couldn't read first grid line to determine grid dimensions");
    }

    // and put it back to make the next loop easier (!)
    file_.seekg(first_line_cache);

    const size_t dim_x = line.size();
    grid current({dim_x, dim_x});

    for ( size_t y = 0; y < dim_x; ++y )
    {
        if ( !std::getline(file_, line) )
        {
            throw grid_read_error("couldn't read line during grid assigment");
        }
        for ( size_t x = 0; x < dim_x; ++x )
        {
            current.at({x, y}).set_value(line[x]-'0');
        }
    }
    return current;
}
