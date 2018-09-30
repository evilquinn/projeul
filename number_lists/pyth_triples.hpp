
#ifndef NUMBER_LISTS_PYTH_TRIPLES_HPP
#define NUMBER_LISTS_PYTH_TRIPLES_HPP

#include <cstddef>
#include <set>
#include <stdexcept>
#include <ostream>

namespace pyth { // pythagoras

// model a pythagorean triplet, a and b are interchangable if you know what
// I mean
class triplet
{
public:
    triplet(size_t a, size_t b);
    triplet(size_t a, size_t b, size_t c);
    const size_t a;
    const size_t b;
    const size_t c;
    bool less_than(const triplet& rhs) const;
    bool equal(const triplet& rhs) const;
    using invalid_argument = std::invalid_argument;

private:
    size_t calc_c();
    const size_t sadj;
    const size_t ladj;
};

inline bool operator<( const triplet& lhs, const triplet& rhs )
{
    return lhs.less_than(rhs);
}
inline bool operator==( const triplet& lhs, const triplet& rhs )
{
    return lhs.equal(rhs);
}
inline bool operator<=( const triplet& lhs, const triplet& rhs )
{
    return lhs == rhs || lhs < rhs;
}
inline bool operator>=( const triplet& lhs, const triplet& rhs )
{
    return rhs < lhs;
}
inline bool operator>( const triplet& lhs, const triplet& rhs )
{
    return rhs <= lhs;
}

using triplets_t = std::set<triplet>;

triplets_t gen_triplets(size_t a);

} // end namespace pyth

inline std::ostream& operator<<( std::ostream& os, const pyth::triplet& to_s )
{
    return os << "{" << to_s.a << "," << to_s.b << "," << to_s.c << "}";
}

#endif  // NUMBER_LISTS_PYTH_TRIPLES_HPP
