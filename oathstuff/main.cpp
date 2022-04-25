
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

#include <getopt.h>

#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/writer.h>

#include "key_data.hpp"
#include "config.hpp"
#include "display.hpp"


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
