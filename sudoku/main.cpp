
#include <iostream>
#include <sudoku/square.hpp>
#include <sudoku/grid.hpp>

int main()
{
    const evilquinn::sudoku::dimensions dim = { 9, 9 };
    evilquinn::sudoku::grid g(dim);

    std::cout << g.to_string() << std::endl;

    return 0;
}
