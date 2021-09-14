
#include <iostream>
#include <sstream>
#include <memory>
#include <sudoku/grid.hpp>
#include <sudoku/grid_reader.hpp>
#include <sudoku/solver.hpp>
#include <signal_handler/signal_handler.hpp>

namespace evilquinn
{
// undefined if grid isn't solved
// return number represented by the 3 leftmost digits on top row
size_t get_magic(sudoku::grid& grid)
{
    size_t result = 0;
    for ( size_t i = 0; i < 3; ++i )
    {
        result *= 10;
        result += *grid.at({ i, 0 }).value();
    }
    return result;
}
}

int main()
{
    evilquinn::register_signal_handler();
#if 1
    evilquinn::sudoku::grid_reader reader(
        "/home/evilquinn/git/projeul/sudoku/p096_sudoku_difficult.txt" );

    size_t total_remaining = 0;
    size_t magic_result = 0;
    while ( auto grid_from_file = reader.getgrid() )
    {
        evilquinn::sudoku::solver( *grid_from_file ).solve();
        std::cout << *grid_from_file << std::endl;
        size_t remaining = grid_from_file->count_remaining();
        total_remaining += remaining;
        if ( remaining == 0 ) magic_result += evilquinn::get_magic(*grid_from_file);
    }
    std::cout << total_remaining << std::endl;
    std::cout << "magic: " << magic_result << std::endl;
#endif

    return 0;
}
