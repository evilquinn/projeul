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
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>
#include <fstream>


#if !defined(PROJEUL_AOC_PATH)
#define PROJEUL_AOC_PATH "."
#endif

class picture
{
public:
    typedef std::string data_type;
    typedef data_type::iterator iterator;
    typedef data_type::const_iterator const_iterator;
    typedef data_type::size_type size_type;

    picture(const data_type& data, size_type w, size_type h) :
        data_(data),
        width_(w),
        height_(h),
        layer_size_(width_*height_),
        layers_(data.size() / layer_size_)
    {
        if ( layer_size_ * layers_ != data.size() )
        {
            std::ostringstream msg;
            msg << "failed construct picture of width: " << width_
                << ", heigth: " << height_
                << " with data size: " << data.size();
            throw std::runtime_error(msg.str());
        }
    }

    data_type data_;
    size_type width_;
    size_type height_;
    size_type layer_size_;
    size_type layers_;

private:
};

int elf_check(const picture& p)
{
    // find the layer that contains the fewest 0 digits. On that layer, what
    // is the number of 1 digits multiplied by the number of 2 digits?
    const char least_of = '0';
    int num_zeroes = std::numeric_limits<int>::max();
    auto least_zeroes = p.data_.end();
    std::unordered_map<char, int> least_counts;
    for ( auto it = p.data_.begin(); it != p.data_.end(); std::advance(it, p.layer_size_) )
    {
        std::unordered_map<char, int> layer_counts;
        std::for_each(it, std::next(it, p.layer_size_), [&](char c){ ++layer_counts[c]; });
        if ( layer_counts[least_of] < num_zeroes )
        {
            num_zeroes = layer_counts[least_of];
            least_zeroes = it;
            least_counts = layer_counts;
        }
    }
    size_t ones = least_counts['1'];
    size_t twos = least_counts['2'];
    size_t result = ones * twos;
    return result;
}

std::ostream& operator<<(std::ostream& os, const picture& p)
{
    for ( auto it = p.data_.begin(); it != p.data_.end(); /* noop */ )
    {
        os << "Layer " << std::distance(p.data_.begin(), it) / p.layer_size_ << ":\n";
        for ( auto linlim = std::next(it, p.layer_size_); it != linlim; std::advance(it, p.width_) )
        {
            std::copy(it, std::next(it, p.width_), std::ostream_iterator<char>(os));
            os << "\n";
        }
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
        std::cout << "elf: " << picture(datum.first, datum.second.first, datum.second.second) << "\n";
    }

    std::ifstream ifs(PROJEUL_AOC_PATH "/08_input.txt");
    std::string super_data;
    ifs >> super_data;
    picture super_pic(super_data, 25, 6 );
    auto result = elf_check(super_pic);
    std::cout << "result: " << result << "\n";

    return 0;
}
