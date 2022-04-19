
#include <iostream>
#include <vector>

#include <ctime>

#include <boost/random.hpp>
#include <boost/random/uniform_int.hpp>

const std::string plaintext  = "The quick brown fox jumped over the lazy dog";
const std::string ciphertext = "Gur dhvpx oebja sbk whzcrq bire gur ynml qbt";

typedef std::string buf_type;
typedef boost::random::mt19937 random_algorithm;
typedef boost::random::uniform_int_distribution<size_t> number_between;
typedef boost::random::variate_generator<random_algorithm, number_between> number_generator;

class chunker
{
public:
    chunker(const buf_type::value_type* buf, size_t buf_size) :
        buf_(buf),
        buf_size_(buf_size),
        pos_(0)
    {}
    bool get_chunk(const buf_type::value_type*& chunk, size_t& chunk_size)
    {
        if ( pos_ == buf_size_ ) return false; // don't call again

        // what's the next chunk size?
        size_t next_chunk_size = jenny_();
        size_t remaining = buf_size_ - pos_;
        if ( next_chunk_size > remaining ) next_chunk_size = remaining;
        // return the next chunk
        chunk = buf_ + pos_;
        chunk_size = next_chunk_size;
        // move our position along
        pos_ += chunk_size;
        // testing
        chunk_sizes.push_back(next_chunk_size);
        // call again
        return true;
    }
    bool get_remaining(const buf_type::value_type*& chunk, size_t& chunk_size)
    {
        if ( pos_ == buf_size_ ) return false;

        chunk = buf_ + pos_;
        chunk_size = buf_size_ - pos_;
        pos_ = buf_size_;
        chunk_sizes.push_back(chunk_size);
        return true;
    }
private:
    const buf_type::value_type* const buf_;
    const size_t buf_size_;
    size_t pos_;
    static number_generator jenny_;
public:
    std::vector<size_t> chunk_sizes; // testing
};
number_generator chunker::jenny_(random_algorithm(std::time(NULL)), number_between(0, 10));
class transformer
{
public:
    transformer() :
        chuck_(ciphertext.data(), ciphertext.size()),
        chunk_sizes(chuck_.chunk_sizes)
    {}
    buf_type apply(const buf_type& buf)
    {
        cache.insert(cache.end(), buf.begin(), buf.end());

        buf_type result;
        const buf_type::value_type* next_begin = NULL;
        size_t next_size = 0;
        if ( chuck_.get_chunk(next_begin, next_size) )
        {
            result.resize(next_size);
            memcpy(&result[0], next_begin, next_size);
        }

        return result;
    }
    buf_type finalise()
    {
        buf_type result;
        const buf_type::value_type* next_begin = NULL;
        size_t next_size = 0;
        if ( chuck_.get_remaining(next_begin, next_size) )
        {
            result.resize(next_size);
            memcpy(&result[0], next_begin, next_size);
        }
        return result;
    }
private:
    chunker chuck_;
public:
    buf_type cache;
    std::vector<size_t>& chunk_sizes;
};

void do_stuff()
{
    buf_type data_in(plaintext.begin(), plaintext.end());
    chunker chuck(data_in.data(), data_in.size());
    transformer tranny;

    buf_type transformed;
    buf_type next_transformed;


    const buf_type::value_type* next_begin = NULL;
    size_t next_size = 0;
    while ( chuck.get_chunk(next_begin, next_size) )
    {
        // while there's data to send
        buf_type working(next_begin, next_begin+next_size);
        // send it
        next_transformed = tranny.apply(working);
        // append interim result
        transformed.insert(transformed.end(),
                           next_transformed.begin(),
                           next_transformed.end());
    }
    // and get whatever remains
    next_transformed = tranny.finalise();
    transformed.insert(transformed.end(),
                        next_transformed.begin(),
                        next_transformed.end());

    std::cout << "Expected: " << plaintext << "\n"
              << "Sent:     " << tranny.cache << "\n"
              << "Chunks:   ";
    std::string sep = "";
    for ( auto&& chunk_size : chuck.chunk_sizes )
    {
        std::cout << sep << chunk_size;
        sep = ", ";
    }
    std::cout << "\n"
              << ( plaintext == tranny.cache ? "SUCCESS" : "FAILED" ) << std::endl;
    std::cout << "Expected: " << ciphertext << "\n"
              << "Got:      " << transformed << "\n"
              << "Chunks:   ";
    sep = "";
    for ( auto&& chunk_size : tranny.chunk_sizes )
    {
        std::cout << sep << chunk_size;
        sep = ", ";
    }
    std::cout << "\n"
              << ( ciphertext == transformed ? "SUCCESS" : "FAILED" ) << std::endl;

}

int main()
{
    std::cout << "hello" << std::endl;
    do_stuff();
    return 0;
}
