#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

#include <sudoku/solver.hpp>
#include <sudoku/grid_reader.hpp>

using ::testing::Eq;
using ::testing::StrEq;

TEST( SudokuSolverTest, TestSolverMatchesExpected )
{
    evilquinn::sudoku::grid_reader reader(
        "/home/evilquinn/git/projeul/sudoku/test/test_unsolved_sudoku.txt" );
    evilquinn::sudoku::grid_reader solved_reader(
        "/home/evilquinn/git/projeul/sudoku/test/test_solved_sudoku.txt" );

    while ( auto grid_from_file = reader.getgrid() )
    {
        auto solved_from_file = solved_reader.getgrid();

        evilquinn::sudoku::solver( *grid_from_file ).solve();
        std::ostringstream solvered;
        solvered << *grid_from_file;
        std::ostringstream solveds;
        solveds << *solved_from_file;
        EXPECT_EQ ( solvered.str(), solveds.str() );
    }
}

TEST( SudokuSolverTest, TestSolverXWing)
{
    std::string x_wing_grid =
    "\n"
    "000000000\n"
    "000000000\n"
    "000000000\n"
    "000000000\n"
    "000000000\n"
    "000000000\n"
    "000000000\n"
    "000000000\n"
    "000000000";
    std::istringstream ins(x_wing_grid);
    evilquinn::sudoku::grid_reader xreader(std::move(ins));
    auto grid = xreader.getgrid();
    std::vector<evilquinn::sudoku::coord> elim_from = {
        { 0, 1 },
        { 2, 1 },
        { 3, 1 },
        { 4, 1 },
        { 5, 1 },
        { 6, 1 },
        { 8, 1 },
        { 0, 7 },
        { 2, 7 },
        { 3, 7 },
        { 4, 7 },
        { 5, 7 },
        { 6, 7 },
        { 8, 7 }
    };
    for ( auto&& elim_from_coord : elim_from )
    {
        grid->at(elim_from_coord).eliminate(5);
    }
    evilquinn::sudoku::solver(*grid).x_wing();
}
