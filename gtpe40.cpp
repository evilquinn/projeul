#include <iostream>


//      9 x 1 digit:         1 @ d_1      ..        9 @ d_9
//     90 x 2 digit:      1(0) @ d_10     ..     (9)9 @ d_189
//    900 x 3 digit:     1(00) @ d_190    ..    (99)0 @ d_2889
//   9000 x 4 digit:    1(000) @ d_2890   ..   (999)9 @ d_38889
//  90000 x 5 digit:   1(0000) @ d_38890  ..  (9999)9 @ d_488889
// 900000 x 6 digit:  1(00000) @ d_488890 .. (99999)9 @ d_5888889


struct range
{
    bool contains(unsigned int n) const;
    void advance();

    unsigned int digit_at(unsigned int n) const;


    private:

    unsigned int digits = 1;

    unsigned int num_begin = 1;

    unsigned int index_begin = 1;
    unsigned int index_end   = 10;
};


bool range::contains(unsigned int n) const
{
    return index_begin <= n && n < index_end;
}


void range::advance()
{
    ++digits;
    num_begin *= 10;

    index_begin  = index_end;
    index_end   += 9 * num_begin * digits;
}


unsigned int range::digit_at(unsigned int n) const
{
    auto const offset = n - index_begin;
    auto       number = num_begin + offset / digits;

    for(auto i = digits - 1 - offset % digits; i; --i)
    {
        number /= 10;
    }

    return number % 10;
}


int main(int, char**)
{
    auto answer = 1U;
    auto r      = range{};


    for(auto n = 1U; n <= 1000000; n *= 10)
    {
        while(!r.contains(n))
        {
            r.advance();
        }

        answer *= r.digit_at(n);
    }

    std::cout << answer << '\n';


    return 0;
}
