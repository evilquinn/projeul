/**
 *
 * The Elves' spirits are lifted when they realize you have an opportunity to reboot one of their Mars rovers,
 * and so they are curious if you would spend a brief sojourn on Mars. You land your ship near the rover.
 *
 * When you reach the rover, you discover that it's already in the process of rebooting! It's just waiting for
 * someone to enter a BIOS password. The Elf responsible for the rover takes a picture of the password (your puzzle input)
 * and sends it to you via the Digital Sending Network.
 *
 * Unfortunately, images sent via the Digital Sending Network aren't encoded with any normal encoding; instead,
 * they're encoded in a special Space Image Format. None of the Elves seem to remember why this is the case.
 * They send you the instructions to decode it.
 *
 * Images are sent as a series of digits that each represent the color of a single pixel. The digits fill each row
 * of the image left-to-right, then move downward to the next row, filling rows top-to-bottom until every pixel of
 * the image is filled.
 *
 * Each image actually consists of a series of identically-sized layers that are filled in this way. So, the first
 * digit corresponds to the top-left pixel of the first layer, the second digit corresponds to the pixel to the right
 * of that on the same layer, and so on until the last digit, which corresponds to the bottom-right pixel of the last layer.
 *
 * For example, given an image 3 pixels wide and 2 pixels tall, the image data 123456789012 corresponds to
 * the following image layers:
 *
 * Layer 1: 123
 *          456
 *
 * Layer 2: 789
 *          012
 *
 * The image you received is 25 pixels wide and 6 pixels tall.
 *
 * To make sure the image wasn't corrupted during transmission, the Elves would like you to find the layer that
 * contains the fewest 0 digits. On that layer, what is the number of 1 digits multiplied by the number of 2 digits?
 *
 */


#include <iostream>
#include <vector>
#include <fstream>


#if !defined(PROJEUL_AOC_PATH)
#define PROJEUL_AOC_PATH "."
#endif
/**
struct layer
{
    typedef std::vector<int> line;
    std::vector<line> lines;
}**/

using line = std::string;
using layer = std::vector<line>;
using picture = std::vector<layer>;

picture to_picture(const std::string& s, size_t w, size_t h)
{
    picture result = {};
    auto it = s.begin();
    while ( it != s.end() )
    {
        result.push_back({});
        for ( size_t i = 0; i < h; ++i )
        {
            result.rbegin()->push_back({});
            std::copy(it, std::next(it, w), std::back_inserter(*result.rbegin()->rbegin()));
            std::advance(it, w);
        }
    }
    return result;
}

int elf_check(const picture& pic)
{
    // find the layer that contains the fewest 0 digits. On that layer, what
    // is the number of 1 digits multiplied by the number of 2 digits?
    int num_zeroes = std::numeric_limits<int>::max();
    auto least_zeroes = pic.end();
    for ( auto&& layer : pic )
    {
        int num_zeroes_this_layer = 0;
        for ( auto&& line : layer )
        {
            num_zeroes_this_layer += std::count(line.begin(), line.end(), 0);
        }
        if ( num_zeroes_this_layer < num_zeroes )
        {
            num_zeroes = num_zeroes_this_layer;
            // todo: fix least_zeroes
        }

    }

}

std::ostream& operator<<(std::ostream& os, const picture& p)
{
    std::string space = "";
    int idx = 0;
    for ( auto&& layer : p )
    {
        os << "Layer " << ++idx << ":\n";
        for ( auto&& line : layer )
        {
            os << space << line << "\n";
        }
        space.append("  ");
    }
    return os;
}

int main()
{
    std::vector<std::pair<std::string, std::pair<int, int> > > data = {
        { "123456789012", { 3, 2 } }
    };

    for ( auto&& datum : data )
    {
        std::cout << to_picture(datum.first, datum.second.first, datum.second.second) << "\n";
    }
/**
    std::ifstream ifs(PROJEUL_AOC_PATH "/08_input.txt");
    std::string ins;
    while ( ifs >> ins )
    {
        std::cout << ins << std::endl;

    }
*/

    return 0;
}
