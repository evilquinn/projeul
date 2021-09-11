
#ifndef SUDOKU_GRID_READER_HPP
#define SUDOKU_GRID_READER_HPP

#include <boost/optional.hpp>
#include <iosfwd>
#include <memory>
#include <sudoku/grid.hpp>

namespace evilquinn
{
namespace sudoku
{
class grid_reader
{
public:
    grid_reader( const std::string& file );
    grid_reader( std::istringstream iss );
    boost::optional<grid> getgrid();

    class input_error : public std::runtime_error
    {
    public:
        input_error( std::string what )
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
    std::unique_ptr<std::istream> input_owner_;
    std::istream& input_;
};

}  // end namespace sudoku
}  // end namespace evilquinn
#endif  // SUDOKU_GRID_READER_HPP
