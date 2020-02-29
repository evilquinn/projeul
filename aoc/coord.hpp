
#ifndef AOC_COORD_HPP
#define AOC_COORD_HPP

#include <iosfwd>

namespace coord_util
{

struct coord { size_t x = 0; size_t y = 0; };

bool operator< (const coord& a, const coord& b);
std::ostream& operator<< (std::ostream& os, const coord& c);
coord& operator+= (coord& lhs, coord rhs);
coord operator+ (coord lhs, coord rhs);
coord& operator-= (coord& lhs, coord rhs);
coord operator- (coord lhs, coord rhs);
bool within_limit(const coord& a, const coord& b);
bool operator==(const coord& a, const coord& b);

struct coord_incrementer
{
    size_t x_limit = 0;
    void operator()(coord& c, int by = 1) const;
};

} // end namaspace coord_util

#endif // AOC_COORD_HPP
