
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <iterator>
#include <chrono>
#include <ctime>
#include <string_view>
#include <boost/regex.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <liboath/oath.h>
#include <ansi/escapes.hpp>

#ifndef OATHSTUFF_DIR
#define OATHSTUFF_DIR "."
#endif

struct key_data
{
    typedef std::vector<uint8_t> key_type;
    std::string id;
    key_type key;
    size_t totps_digits;
    key_data()
    {}
    explicit key_data(std::string id) :
        id(id)
    {}
    key_data(std::string id, std::vector<uint8_t> key) :
        id(id),
        key(key)
    {}
};
std::ostream& operator<< (std::ostream& os, struct key_data data)
{
    os << "{ \"id\": \"" << data.id << "\", \"key\": \"";
    boost::algorithm::hex(data.key, std::ostream_iterator<char>(os));
    return os << "\" }";
}
typedef std::vector<key_data> keys_data_type;
class keys_reader
{
public:
    virtual keys_data_type read_keys(std::istream& is) const = 0;
};
class keys_reader_authenticator : public keys_reader
{
public:
    keys_reader_authenticator()
    {}
    keys_data_type read_keys(std::istream& is) const
    {
        keys_data_type keys;
        std::string line;
        while ( std::getline(is, line) )
        {
            boost::smatch matches;
            if ( boost::regex_search(line, matches, capture_pattern_) )
            {
                keys.emplace_back(std::string(matches[2]));
                std::string key_str(matches[1]);
                char* binkey;
                size_t binkey_size = 0;
                auto decode_result =
                    oath_base32_decode(key_str.data(),
                                       key_str.size(),
                                       &binkey,
                                       &binkey_size);
                if ( decode_result != OATH_OK ) throw decode_result;
                keys.back().key.resize(binkey_size);
                memcpy(keys.back().key.data(), binkey, binkey_size);
                keys.back().totps_digits = 6; // default everything to 6 digits for now
            }
        }
        return keys;
    }
private:
    static const boost::regex capture_pattern_;
};
const boost::regex keys_reader_authenticator::capture_pattern_(
    "\\?secret=([A-Za-z0-9]*)\\&issuer=([a-zA-Z0-9]*)");

class totps_display
{
public:
    totps_display(boost::asio::io_context& asio_context, keys_data_type keys) :
        asio_context_(asio_context),
        timer_(asio_context),
        keys_(keys)
    {
        std::cout << "screen updating..." << std::endl;
        for ( size_t i = 0; i < keys_.size(); ++i )
        {
            std::cout << "\n";
        }
        asio_context_.post(boost::bind(&totps_display::update, this));
    }
private:
    void update()
    {
        generate();
        std::cout << ansi_escapes::move::left(1000) << ansi_escapes::move::up(keys_.size()) << std::flush;
        for ( size_t i = 0; i < keys_.size(); ++i )
        {
            std::cout << "| " << keys_[i].id << "\t | " << totps_[i] << "\t |" << std::endl;
        }
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&totps_display::update, this));
    }

    void generate()
    {
        totps_.resize(keys_.size());
        for ( size_t i = 0; i < keys_.size(); ++i )
        {
            totps_[i].resize(keys_[i].totps_digits + 1);
            int gen_result = oath_totp_generate(reinterpret_cast<char*>(keys_[i].key.data()),
                                                keys_[i].key.size(),
                                                std::time(NULL),
                                                OATH_TOTP_DEFAULT_TIME_STEP_SIZE,
                                                OATH_TOTP_DEFAULT_START_TIME,
                                                keys_[i].totps_digits,
                                                totps_[i].data());
            if ( gen_result != OATH_OK ) throw gen_result;
        }
    }

    boost::asio::io_context& asio_context_;
    boost::asio::deadline_timer timer_;
    keys_data_type keys_;
    std::vector<std::string> totps_;
};

int main()
{
    std::ifstream thef(OATHSTUFF_DIR "/authenticator.txt");
    std::unique_ptr<keys_reader> reader =
        std::make_unique<keys_reader_authenticator>();
    auto keys = reader->read_keys(thef);
    boost::asio::io_context asio_context;
    totps_display display(asio_context, keys);
    asio_context.run();
    return 0;
}
