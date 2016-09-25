#ifndef KNOWN_PRIMES_HPP_
#define KNOWN_PRIMES_HPP_

#include <set>
#include <stddef.h>

#define KNOWN_PRIMES_LIMIT 104729

class known_primes
{
public:
    known_primes();
    virtual ~known_primes();

    std::set<size_t>& set()
    {
        return *known_primes_;
    }
private:
    std::set<size_t>* known_primes_;
};

#endif // KNOWN_PRIMES_HPP_
