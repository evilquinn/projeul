
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <iterator>
#include <chrono>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <cstdio>
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

const char* env_home = std::getenv("HOME");
const std::string user_config_dir_path_prefix = env_home ? env_home : ".";
const std::string user_config_dir_path = user_config_dir_path_prefix + "/.otps";
const std::string user_keys_file_path = user_config_dir_path + "/keys";


struct key_data
{
    typedef std::vector<uint8_t> key_type;
    std::string id;
    key_type key;
    size_t digits;
    size_t interval;
    size_t offset;
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
    os << "\", \"digits\": \"" << data.digits << "\", \"interval\": \"" << data.interval << "\", \"offset\": \"" << data.offset << "\" }";
    return os;
}
typedef std::vector<key_data> keys_data_type;
class keys_reader
{
public:
    virtual keys_data_type read_keys(std::istream& is) const = 0;
};

class config
{
public:
    config() :
        user_dir_path_(user_config_dir_path),
        user_keys_path_(user_keys_file_path)
    {
        init();
    }
    void save_keys(keys_data_type keys)
    {
        keys_ = std::move(keys);
        auto temp_keys_file = std::tmpfile();
        if ( !temp_keys_file ) throw std::runtime_error("failed to open temp file");
    }
private:
    void init()
    {
        // check config dir exists
        auto dir_status = std::filesystem::status(user_dir_path_);
        if ( ! std::filesystem::exists(dir_status) ) return; // no config dir, fair enough
        if ( ! std::filesystem::is_directory(dir_status) ) throw std::runtime_error("config dir isn't a dir");
        auto keys_status = std::filesystem::status(user_keys_path_);
        if ( ! std::filesystem::exists(keys_status) ) return; // no keys file, fair enough
        if ( ! std::filesystem::is_regular_file(keys_status) ) throw std::runtime_error("keys file is not regular file");
        auto keys_perms = keys_status.permissions();
        if ( ( keys_perms & ( std::filesystem::perms::group_all |
                              std::filesystem::perms::others_all ) )
                 != std::filesystem::perms::none ) throw std::runtime_error("keys file incorrect perms");
    }
    std::filesystem::path user_dir_path_;
    std::filesystem::path user_keys_path_;
    keys_data_type keys_;
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
                keys.back().digits = 6; // default everything to 6 digits for now
                keys.back().interval = OATH_TOTP_DEFAULT_TIME_STEP_SIZE;
                keys.back().offset = OATH_TOTP_DEFAULT_START_TIME;
            }
        }
        return keys;
    }
private:
    static const boost::regex capture_pattern_;
};
const boost::regex keys_reader_authenticator::capture_pattern_(
    "\\?secret=([A-Za-z0-9]*)\\&issuer=([a-zA-Z0-9]*)");

class rotating_string
{
public:
    rotating_string()
    {}
    rotating_string(std::string s, size_t width) :
        s_(s),
        width_(width),
        i_(0)
    {}
    std::string get()
    {
        size_t to_display = s_.size() - i_;
        if ( to_display <= width_ )
        {
            auto result = s_.substr(i_, to_display);
            i_ = 0;
            result.append(width_ - to_display, ' ');
            return result;
        }
        size_t can_display = width_ - num_dots;
        std::string result(s_.data() + i_, can_display);
        result.append("..");
        ++i_;
        return result;
    }
private:
    static const size_t num_dots = 2;
    std::string s_;
    size_t width_;
    size_t i_;
};
class totps_display
{
public:
    totps_display(boost::asio::io_context& asio_context, keys_data_type keys) :
        asio_context_(asio_context),
        timer_(asio_context)
    {
        states_.resize(keys.size());
        for ( size_t i = 0; i < keys.size(); ++i )
        {
            std::cout << "\n"; // prepare screen real estate
            states_[i].display_name = rotating_string(keys[i].id, 20);
            states_[i].key_info = keys[i];
        }
        asio_context_.post(boost::bind(&totps_display::update, this));
    }
private:
    void update()
    {
        generate_totps();
        std::cout << ansi_escapes::move::left(1000) << ansi_escapes::move::up(states_.size());
        for ( size_t i = 0; i < states_.size(); ++i )
        {
            std::cout << "| " << states_[i].display_name.get()
                      << " | " << std::setw(8) << states_[i].totp
                      << " | " << std::setw(3) << states_[i].seconds_to_update << "s"
                      << " |" << std::endl;
        }
        timer_.expires_from_now(boost::posix_time::seconds(1));
        timer_.async_wait(boost::bind(&totps_display::update, this));
    }

    void generate_totps()
    {
        for ( size_t i = 0; i < states_.size(); ++i )
        {
            states_[i].totp.resize(states_[i].key_info.digits + 1);
            time_t time_now = std::time(NULL);
            states_[i].seconds_to_update =
                states_[i].key_info.interval -
                    ( (time_now - states_[i].key_info.offset) % states_[i].key_info.interval );
            int gen_result = oath_totp_generate(reinterpret_cast<char*>(states_[i].key_info.key.data()),
                                                states_[i].key_info.key.size(),
                                                time_now,
                                                states_[i].key_info.interval,
                                                states_[i].key_info.offset,
                                                states_[i].key_info.digits,
                                                &states_[i].totp[0]);
            if ( gen_result != OATH_OK ) throw gen_result;
        }
    }

    boost::asio::io_context& asio_context_;
    boost::asio::deadline_timer timer_;

    struct state
    {
        std::string totp;
        rotating_string display_name;
        key_data key_info;
        size_t seconds_to_update;
    };
    std::vector<state> states_;

};

int main()
{
    config c;
    std::ifstream thef(OATHSTUFF_DIR "/authenticator.txt");
    std::unique_ptr<keys_reader> reader =
        std::make_unique<keys_reader_authenticator>();
    auto keys = reader->read_keys(thef); c.save_keys(keys);
    boost::asio::io_context asio_context;
    totps_display display(asio_context, keys);
    asio_context.run();

    //rotating_string rot13("jimmyJango", 5);
    //for ( size_t i = 0; i < 10; ++i )
    //{
    //    std::cout << i << ": " << rot13.get() << std::endl;
    //}
    return 0;
}
