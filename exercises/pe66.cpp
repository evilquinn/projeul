/*
 * pe66.cpp
 *
 *  Created on: 13 Jun 2015
 *      Author: evilquinn
 */

#include "pe66.hpp"
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

static int gcd(int a, int b)
{
    return (b==0)?a:gcd(b,a%b);
}

std::vector<int> pe66::continued_fraction_of_root_of(const int n)
{
    std::vector<int> result;

    int s = n;
    // s = a*a + r
    // => Vs = a + ( 1 / a + Vs )
    //
    int a = 1;
    while ( a * a < s )
    {
        ++a;
    }
    --a;
    result.push_back(a);

    if ( a * a == s )
    {
        return result;
    }

    // I stole this algo from
    // https://dansesacrale.wordpress.com/2010/07/04/continued-fractions-sqrt-steps/
    // Cheers.
    int b = a, c = 1, d, e, f, g;
    while(true)
    {
        d=c;
        c=n-b*b;
        g=gcd(c,d);
        c/=g;
        d/=g;
        b=-b;
        f=a-c;
        for(e=0;b<=f;e++)
        {
            b+=c;
        }
        result.push_back(e);
        if(b==a&&c==1)
        {
            return result;
        }
    }

    return result;
}

bool pe66::is_square(boost::multiprecision::cpp_int n)
{
    boost::multiprecision::cpp_int test = boost::multiprecision::sqrt(n);
    return (test * test) == n;
}

template<typename Container>
class continued_fraction
{
public:
    continued_fraction(Container& container) :
        container_(container)
    {}
    Container& container_;
};

template<typename Container>
continued_fraction<Container> to_continued_fraction(Container& cf)
{
    return continued_fraction<Container>(cf);
}

template<typename Container>
std::ostream& operator<< (std::ostream& os, continued_fraction<Container> cf)
{
    if ( cf.container_.size() == 0 )
    {
        return os;
    }
    os << cf.container_.at(0) << ":";
    for ( auto it = cf.container_.begin() + 1; it != cf.container_.end(); ++it)
    {
        os << *it << ",";
    }
    return os;
}

std::string& pe66::name() { return name_; }
void         pe66::run()
{
    /*
     * Consider quadratic Diophantine equations of the form:
     *
     * x^2 – Dy^2 = 1
     *
     * For example, when D=13, the minimal solution in x is
     *   649^2 – 13×180^2 = 1.
     *
     * It can be assumed that there are no solutions in positive integers
     * when D is square.
     *
     * By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain
     * the following:
     *
     *     3^2 – 2×2^2 = 1
     *     2^2 – 3×1^2 = 1
     * (!) 9^2 – 5×4^2 = 1
     *     5^2 – 6×2^2 = 1
     *     8^2 – 7×3^2 = 1
     *
     * Hence, by considering minimal solutions in x for D ≤ 7, the largest
     * x is obtained when D = 5.
     *
     * Find the value of D ≤ 1000 in minimal solutions of x for which the
     * largest value of x is obtained.
     *
     */

    size_t result = 0;
    size_t limit = 1000;

    for ( size_t D = 2; D <= limit; ++D )
    {
        if ( ! is_square(D) )
        {
            std::cout << D << ": ";
            auto d_cont_fract = continued_fraction_of_root_of(D);
            std::cout << to_continued_fraction(d_cont_fract) << "\n";
        }

    }

    std::cout << "result : " << result << std::endl;
}
