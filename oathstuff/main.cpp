
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <iterator>
#include <string_view>
#include <boost/regex.hpp>
#include <boost/algorithm/hex.hpp>
#include <liboath/oath.h>

#ifndef OATHSTUFF_DIR
#define OATHSTUFF_DIR "."
#endif

struct key_data
{
    typedef std::vector<uint8_t> key_type;
    std::string id;
    key_type key;
    key_data()
    {}
    key_data(std::string id) :
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
            }
        }
        return keys;
    }
private:
    static const boost::regex capture_pattern_;
};
const boost::regex keys_reader_authenticator::capture_pattern_(
    "\\?secret=([A-Za-z0-9]*)\\&issuer=([a-zA-Z0-9]*)");

int main()
{
    std::cout << "hello" << std::endl;
    std::ifstream thef(OATHSTUFF_DIR "/authenticator.txt");
    std::unique_ptr<keys_reader_authenticator> reader =
        std::make_unique<keys_reader_authenticator>();
    auto keys = reader->read_keys(thef);
    for ( auto&& key : keys )
    {
        std::cout << "key: " << key << std::endl;
    }
    return 0;
}
