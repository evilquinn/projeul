/**
 *
 * Now you're ready to decode the image. The image is rendered by stacking the layers and aligning
 * the pixels with the same positions in each layer. The digits indicate the color of the corresponding
 * pixel: 0 is black, 1 is white, and 2 is transparent.
 *
 * The layers are rendered with the first layer in front and the last layer in back. So, if a given
 * position has a transparent pixel in the first and second layers, a black pixel in the third layer,
 * and a white pixel in the fourth layer, the final image would have a black pixel at that position.
 *
 * For example, given an image 2 pixels wide and 2 pixels tall, the image data 0222112222120000 corresponds
 * to the following image layers:
 *
 * Layer 1: 02
 *          22
 *
 * Layer 2: 11
 *          22
 *
 * Layer 3: 22
 *          12
 *
 * Layer 4: 00
 *          00
 *
 * Then, the full image can be found by determining the top visible pixel in each position:
 *
 * The top-left pixel is black because the top layer is 0.
 * The top-right pixel is white because the top layer is 2 (transparent), but the second layer is 1.
 * The bottom-left pixel is white because the top two layers are 2, but the third layer is 1.
 * The bottom-right pixel is black because the only visible pixel in that position is 0 (from layer 4).
 * So, the final image looks like this:
 *
 * 01
 * 10
 *
 * What message is produced after decoding your image?
 */


#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>
#include <fstream>


#include "../path_def.hpp"

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

class rendering : public picture
{
public:
    rendering(const data_type& data, size_type w, size_type h) :
        picture(data, w, h)
    {}
};


enum class pixel_colour
{
    black = '0',
    white = '1',
    transparent = '2'
};

int elf_check(const picture& p, pixel_colour least_of, pixel_colour multa, pixel_colour multb)
{
    // find the layer that contains the fewest least_of pixels. On that layer, what
    // is the number of multa pixels multiplied by the number of multb pixels?
    std::unordered_map<pixel_colour, int> least_counts = { { least_of, std::numeric_limits<int>::max() } };
    for ( auto it = p.data_.begin(); it != p.data_.end(); std::advance(it, p.layer_size_) )
    {
        std::unordered_map<pixel_colour, int> layer_counts;
        std::for_each(it, std::next(it, p.layer_size_), [&](char c)
        {
            ++layer_counts[static_cast<pixel_colour>(c)];
        });
        if ( layer_counts[least_of] < least_counts[least_of] )
        {
            least_counts = layer_counts;
        }
    }
    size_t as = least_counts[multa];
    size_t bs = least_counts[multb];
    size_t result = as * bs;
    return result;
}

rendering render(const picture& p)
{
    std::string rendered;
    for ( auto it = p.data_.begin(), limit = std::next(it, p.layer_size_); it != limit; ++it )
    {
        rendered.push_back(static_cast<char>(pixel_colour::transparent));
        for ( size_t lidx = 0; lidx < p.layers_; ++lidx )
        {
            char cand = *std::next(it, lidx * p.layer_size_);
            if ( cand != static_cast<char>(pixel_colour::transparent) )
            {
                *rendered.rbegin() = cand;
                break;
            }
        }
    }
    return rendering(rendered, p.width_, p.height_);
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

std::ostream& operator<<(std::ostream& os, const rendering& p)
{
    for ( auto it = p.data_.begin(); it != p.data_.end(); /* noop */ )
    {
        os << "Layer " << std::distance(p.data_.begin(), it) / p.layer_size_ << ":\n";
        for ( auto linlim = std::next(it, p.layer_size_); it != linlim; std::advance(it, p.width_) )
        {
            std::transform(it, std::next(it, p.width_), std::ostream_iterator<char>(os), [](char c)
            {
                pixel_colour p = static_cast<pixel_colour>(c);
                switch(p)
                {
                case pixel_colour::white : return '#';
                // everything else is blank
                default : return ' ';
                } // endswitch
            });
            os << "\n";
        }
    }
    return os;
}


int main()
{
    std::vector<std::pair<std::string, std::pair<int, int> > > data = {
        { "123456789012", { 3, 2 } },
        { "0222112222120000", { 2, 2 } }
    };

    for ( auto&& datum : data )
    {
        auto pic = picture(datum.first, datum.second.first, datum.second.second);
        std::cout << "pic:\n" << pic << "\n";
    }

    std::ifstream ifs(PROJEUL_AOC_PATH "/08_input.txt");
    std::string super_data;
    ifs >> super_data;
    picture super_pic(super_data, 25, 6 );

    auto result = elf_check(super_pic, pixel_colour::black, pixel_colour::white, pixel_colour::transparent);
    std::cout << "result: " << result << "\n";

    std::cout << "rendered:\n" << render(super_pic) << "\n";

    return 0;
}
