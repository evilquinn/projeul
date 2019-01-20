
#ifndef SUDOKU_SQUARE_HPP
#define SUDOKU_SQUARE_HPP

#include <set>
#include <stdexcept>
#include <sstream>

namespace evilquinn
{
namespace sudoku
{

struct coord { size_t x; size_t y; };
std::string to_string(const coord& c);

class square
{
public:
    square(coord pos, size_t num_candidates);
    using candidate_set = std::set<size_t>;
    void eliminate(size_t candidate);
    void eliminate(candidate_set candidates);
    std::string to_string() const;

    class illegal_square : public std::runtime_error
    {
    public:
        illegal_square(std::string what) :
            std::runtime_error(std::move(what))
        {}
    };
private:
    void validate();

    coord pos_;
    candidate_set candidates_;
};

} // end namespace sudoku
} // end namespace square


#endif // SUDOKU_SQUARE_HPP
