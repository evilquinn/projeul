
#include <iostream>
#include <sudoku/square.hpp>
#include <sudoku/grid.hpp>
#include <sudoku/grid_reader.hpp>
#include <sudoku/solver.hpp>

int main()
{
    evilquinn::sudoku::grid_reader reader("/home/evilquinn/git/projeul/sudoku/p096_sudoku.txt");

    while ( auto grid_from_file = reader.getgrid() )
    {
        evilquinn::sudoku::solver().solve(*grid_from_file);
        std::cout << grid_from_file->to_string() << std::endl;
    }

    return 0;
}
