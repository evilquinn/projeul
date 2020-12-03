/*
 * https://adventofcode.com/2019/day/16
 */

#include <iostream>
#include <vector>
#include <array>

namespace
{

int get_multiplier(ptrdiff_t index, ptrdiff_t mult)
{
    static const std::array<int, 4> base_pattern = { 0, 1, 0, -1 };
    return base_pattern[ ( (index + 1) / mult ) % base_pattern.size() ];
}

std::vector<int> fft(const std::vector<int>& cinput, int repeated, int iters)
{
    // fuck it, let's see.
    std::vector<int> input;
    for ( int r = 0; r < repeated; ++r )
    {
        std::copy(cinput.begin(), cinput.end(), std::back_inserter(input));
    }

    for ( int i = 0; i < iters; ++i )
    {
        std::vector<int> output(input.size(), 0);
        for ( size_t out_idx = 0; out_idx < output.size(); ++out_idx )
        {
            for ( size_t in_idx = out_idx; in_idx < input.size(); ++in_idx )
            {
                switch(get_multiplier(in_idx, out_idx+1))
                {
                case -1 : output[out_idx] -= input[in_idx]; break;
                case  1 : output[out_idx] += input[in_idx]; break;
                case  0 : in_idx += out_idx; break;
                }
            }
            output[out_idx] %= 10;
            output[out_idx] = std::abs(output[out_idx]);
        }
        input = std::move(output);
    }
    return input;
}

std::ostream& operator<< ( std::ostream& os, const std::vector<int> data)
{
    if ( !os ) return os;
    size_t count = 0;
    for ( auto&& el : data )
    {
        if ( count == 8 ) break;
        ++count;
        os << el;
    }
    return os;
}

}



int main()
{
    std::vector<std::vector<int> > data =
    {
        { 1, 2, 3, 4, 5, 6, 7, 8 },
        { 8, 0, 8, 7, 1, 2, 2, 4, 5, 8, 5, 9, 1, 4, 5, 4, 6, 6, 1, 9, 0, 8, 3, 2, 1, 8, 6, 4, 5, 5, 9, 5 },
        { 1, 9, 6, 1, 7, 8, 0, 4, 2, 0, 7, 2, 0, 2, 2, 0, 9, 1, 4, 4, 9, 1, 6, 0, 4, 4, 1, 8, 9, 9, 1, 7 },
        { 6, 9, 3, 1, 7, 1, 6, 3, 4, 9, 2, 9, 4, 8, 6, 0, 6, 3, 3, 5, 9, 9, 5, 9, 2, 4, 3, 1, 9, 8, 7, 3 }
    };
    for ( auto&& datum : data )
    {
        auto result = fft(datum, 1, 100);
        std::cout << "result: " << result << "\n";
    }

    std::string input_str = "59712692690937920492680390886862131901538154314496197364022235676243731306353384700179627460533651346711155314756853419495734284609894966089975988246871687322567664499495407183657735571812115059436153203283165299263503632551949744441033411147947509168375383038493461562836199103303184064429083384309509676574941283043596285161244885454471652448757914444304449337194545948341288172476145567753415508006250059581738670546703862905469451368454757707996318377494042589908611965335468490525108524655606907405249860972187568380476703577532080056382150009356406585677577958020969940093556279280232948278128818920216728406595068868046480073694516140765535007";
    std::vector<int> input;
    for ( auto&& ch : input_str )
    {
        input.push_back(ch - '0');
    }
    std::cout << "super: " << fft(input, 10, 100) << "\n";

    return 0;
}
