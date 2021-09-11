
#include <iostream>
#include <sudoku/grid.hpp>
#include <sudoku/grid_reader.hpp>
#include <sudoku/solver.hpp>
#include <signal_handler/signal_handler.hpp>

int main()
{
    evilquinn::register_signal_handler();
    evilquinn::sudoku::grid_reader reader(
        "/home/evilquinn/git/projeul/sudoku/p096_sudoku_single.txt" );

    size_t total_remaining = 0;
    while ( auto grid_from_file = reader.getgrid() )
    {
        evilquinn::sudoku::solver( *grid_from_file ).solve();
        std::cout << *grid_from_file << std::endl;
        total_remaining += grid_from_file->count_remaining();
    }
    std::cout << total_remaining << std::endl;

    return 0;
}
