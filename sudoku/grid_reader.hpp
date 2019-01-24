
#ifndef SUDOKU_GRID_READER_HPP
#define SUDOKU_GRID_READER_HPP

#include <boost/optional.hpp>
#include <fstream>
#include <sudoku/grid.hpp>

namespace evilquinn
{
namespace sudoku
{
class grid_reader
{
public:
    grid_reader( const std::string& file );
    boost::optional<grid> getgrid();

    class file_error : public std::runtime_error
    {
    public:
        file_error( std::string what )
            : std::runtime_error( std::move( what ) )
        {
        }
    };
    class grid_read_error : public std::runtime_error
    {
    public:
        grid_read_error( std::string what )
            : std::runtime_error( std::move( what ) )
        {
        }
    };

private:
    std::ifstream file_;
};

}  // end namespace sudoku
}  // end namespace evilquinn
#endif  // SUDOKU_GRID_READER_HPP
