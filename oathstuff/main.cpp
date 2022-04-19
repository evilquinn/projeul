
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <optional>
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

#include <getopt.h>

#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/writer.h>

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

template<typename OutputStream>
rapidjson::Writer<OutputStream>& operator<< (rapidjson::Writer<OutputStream>& rjw, const struct key_data& data)
{
    rjw.StartObject();
    rjw.Key("id"); rjw.String(data.id.data(), data.id.size());
    std::string hex_key;
    boost::algorithm::hex(data.key, std::back_inserter(hex_key));
    rjw.Key("key"); rjw.String(hex_key.data(), hex_key.size());
    rjw.Key("digits"); rjw.Int64(data.digits);
    rjw.Key("interval"); rjw.Int64(data.interval);
    rjw.Key("offset"); rjw.Int64(data.offset);
    rjw.EndObject();
    return rjw;
}
std::ostream& operator<< (std::ostream& os, const struct key_data& data)
{
    rapidjson::OStreamWrapper osw(os);
    rapidjson::Writer<rapidjson::OStreamWrapper> rjw(osw);
    rjw << data;
    return os;
}
rapidjson::Value& operator>> (rapidjson::Value& json_in, struct key_data& data)
{
    struct key_data result;

    result.id = json_in["id"].GetString();
    boost::algorithm::unhex(json_in["key"].GetString(), std::back_inserter(result.key));
    result.digits = json_in["digits"].GetInt64();
    result.interval = json_in["interval"].GetInt64();
    result.offset = json_in["offset"].GetInt64();

    data = std::move(result);
    return json_in;
}

typedef std::vector<key_data> keys_data_type;
template<typename OutputStream>
rapidjson::Writer<OutputStream>& operator<< (rapidjson::Writer<OutputStream>& rjw, const keys_data_type& data)
{
    rjw.StartArray();
    for ( auto&& key : data )
    {
        rjw << key;
    }
    rjw.EndArray();
    return rjw;
}
rapidjson::Value& operator>> (rapidjson::Value& json_in, keys_data_type& data)
{
    keys_data_type result;
    key_data temp_key;
    for ( auto&& json_key : json_in.GetArray() )
    {
        json_key >> temp_key;
        result.push_back(temp_key);
    }
    data = std::move(result);
    return json_in;
}
class keys_reader
{
public:
    virtual keys_data_type read_keys(std::istream& is) const = 0;
};

class config_file
{
public:
    config_file() :
        user_keys_path_(user_keys_file_path)
    {
        init();
    }
    const keys_data_type& read_keys()
    {
        keys_.clear();

        auto keys_status = std::filesystem::status(user_keys_path_);
        if ( ! std::filesystem::exists(keys_status) ) return keys_; // no keys file, fair enough
        validate_key_file(keys_status);
        auto keys_file = fopen(user_keys_path_.c_str(), "r");
        // prepare the writer
        size_t json_file_stream_buf_size = 1024;
        char json_file_stream_buf[json_file_stream_buf_size];
        auto json_file_stream = rapidjson::FileReadStream(keys_file, json_file_stream_buf, json_file_stream_buf_size);

        rapidjson::Document parsed;
        parsed.ParseStream(json_file_stream);
        parsed >> keys_;
        return keys_;
    }
    void append_keys(keys_data_type keys)
    {
        keys.insert(keys.end(), keys_.begin(), keys_.end());
        save_keys(keys);
    }
    void save_keys(keys_data_type keys)
    {
        // create the new file
        std::string temp_file_name = user_keys_file_path + "-XXXXXX";
        auto temp_keys_fd = mkostemp(&temp_file_name[0], O_WRONLY);
        if ( temp_keys_fd < 0 ) throw std::runtime_error("failed to open temp file");
        auto temp_keys_file = fdopen(temp_keys_fd, "w");
        if ( !temp_keys_file ) throw std::runtime_error("failed to open temp file stream");

        // prepare the writer
        size_t json_file_stream_buf_size = 1024;
        char json_file_stream_buf[json_file_stream_buf_size];
        auto json_file_stream = rapidjson::FileWriteStream(temp_keys_file, json_file_stream_buf, json_file_stream_buf_size);
        auto json_writer = rapidjson::Writer<rapidjson::FileWriteStream>(json_file_stream);

        // write
        json_writer << keys;
        json_file_stream.Flush();
        fclose(temp_keys_file);

        // finally, save
        std::filesystem::rename(temp_file_name, user_keys_path_);
        keys_ = std::move(keys);
    }
private:
    void init()
    {
        auto keys_status = std::filesystem::status(user_keys_path_);
        if ( ! std::filesystem::exists(keys_status) ) return; // no keys file, fair enough
        validate_key_file(keys_status);
    }
    void validate_key_file(const std::filesystem::file_status& status)
    {
        if ( ! std::filesystem::is_regular_file(status) ) throw std::runtime_error("keys file is not regular file");
        auto keys_perms = status.permissions();
        if ( ( keys_perms & ( std::filesystem::perms::group_all |
                              std::filesystem::perms::others_all ) )
                 != std::filesystem::perms::none ) throw std::runtime_error("keys file incorrect perms");
    }
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
        if ( states_.size() == 0 ) std::cout << "\n"; // For the single "No keys..." line
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
        if ( states_.size() == 0 )
        {
            std::cout << "No keys..." << std::endl;
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

enum class import_format
{
    authenticator
};
enum import_format to_import_format(const std::string& s)
{
    if ( s == "authenticator" ) return import_format::authenticator;
    throw std::runtime_error("unrecognised import_format: " + s);
}
const std::string& to_string(const enum import_format i)
{
    switch( i )
    {
    case import_format::authenticator :
    {
        static const std::string authenticator_as_string("authenticator");
        return authenticator_as_string;
    }
    default: throw std::runtime_error("invalid import_format");
    }
}
struct import_options_type
{
    std::string format;
    std::string file_path;
    int verbose;
};
std::ostream& operator<< (std::ostream& os, const struct import_options_type& import_options)
{
    os << "{ \"format\": \"" << import_options.format << "\"";
    if ( import_options.file_path.size() > 0 )
    {
        os << ", \"file_path\": \"" << import_options.file_path << "\"";
    }
    os << ", \"verbose\": " << ( import_options.verbose ? "true" : "false" );
    return os << " }";
}
const struct import_options_type import_options_default = { "authenticator", "", false };
struct import_options_type import_options = import_options_default;
void usage()
{
    std::cout << "Usage: otps import [OPTIONS]\n"
              << "\n"
              << "  imports a list of keys\n"
              << "\n"
              << "Options:\n"
              << "  -h, --help                : display help\n"
              << "  -f, --format format-spec  : use format-spec formatter, supported: authenticator\n"
              << "  -i  --input path          : path to file to import, default: stdin\n"
              << "  -v, --verbose             : enable verbose output\n"
              << std::endl;
    std::cout << "Defaults:\n"
              << import_options_default
              << std::endl;
}
struct import_options_type read_import_options(int argc, char* argv[])
{
    struct import_options_type result = import_options_default;
    static struct option long_options[] =
    {
        { "help",    no_argument,       0, 'h' },
        { "format",  required_argument, 0, 'f' },
        { "input",   required_argument, 0, 'i' },
        { "verbose", no_argument,       &result.verbose, 1 },
        {0, 0, 0, 0}
    };
    int opt_id = 0;
    while ( opt_id != -1 )
    {
        int opt_idx = 0;
        opt_id = getopt_long(argc, argv, "hf:i:v", long_options, &opt_idx);
        if ( opt_id == -1 )
        {
            // end of options
            break;
        }
        switch (opt_id)
        {
        case 'h' : usage();                           break;
        case 'f' : result.format    = optarg; break;
        case 'i' : result.file_path = optarg; break;
        case 'v' : result.verbose   = 1;      break;
        case 0   : break;
        default  : // fall-through
        {
            usage();
            std::exit(EXIT_FAILURE);
        }
        }
    }
    std::cout << "Import Options:\n"
              << result
              << std::endl;
    return result;
}
void import_keys(int argc, char* argv[], config_file& c)
{
    ++optind;
    auto import_options = read_import_options(argc, argv);

    // only authenticator import is supported, they can't select anything else
    keys_reader_authenticator auth_importer;
    std::ifstream ifs;
    std::istream* is;
    if ( import_options.file_path.size() > 0 )
    {
        ifs.open(import_options.file_path.c_str());
        is = &ifs;
    }
    else
    {
        is = &std::cin;
    }
    auto new_keys = auth_importer.read_keys(*is);
    c.append_keys(new_keys);
}
int main(int argc, char* argv[])
{
    config_file c;
    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "import") == 0 )
        {
            import_keys(argc, argv, c);
            return 0;
        }
    }

    boost::asio::io_context asio_context;
    totps_display display(asio_context, c.read_keys());
    asio_context.run();

    return 0;
}
