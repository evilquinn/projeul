#include <gmock/gmock.h>
#include <gtest/gtest.h>

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
