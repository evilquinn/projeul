
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/algorithm/string.hpp>


#include <getopt.h>
#include <liboath/oath.h>

namespace
{

struct configuration
{
    std::string secrets_path;
};
std::ostream& operator<< (std::ostream& os, const struct configuration& config)
{
    os << "secrets_path : " << config.secrets_path << "\n";
    return os;
}
const struct configuration defaults = {
    "~/.ssh/authenticator.txt"
};
struct configuration config = defaults;

void usage()
{
    std::cout << "Usage: auth [OPTIONS]\n"
              << "\n"
              << "  Displays TOPT codes\n"
              << "\n"
              << "Options:\n"
              << "  -h, --help                          : display help\n"
              << "  -f, --secrets-path <secrets_path>   : path to secrets file\n"
              << std::endl;
    std::cout << "Defaults:\n"
              << defaults
              << std::endl;
}


void handle_options(int argc, char* argv[])
{
    static struct option long_options[] =
    {
        { "help",                no_argument,       0, 'h' },
        { "secrets-path",        required_argument, 0, 'f' },
        {0, 0, 0, 0}
    };
    int opt_id = 0;
    while ( opt_id != -1 )
    {
        int opt_idx = 0;
        opt_id = getopt_long(argc, argv, "hf:", long_options, &opt_idx);
        if ( opt_id == -1 )
        {
            // end of options
            break;
        }
        switch (opt_id)
        {
        case 'h' : usage();                         break;
        case 'f' : config.secrets_path    = optarg; break;
        case 0   : break;
        default  : // fall-through
        {
            usage();
            exit(EXIT_FAILURE);
        }
        }
    }

    std::cout << "Config:\n"
              << config
              << std::endl;
}

typedef std::vector<uint8_t> bytes_type;
std::ostream& operator<< (std::ostream& os, const bytes_type& bytes)
{
    for ( auto&& i : bytes )
    {
        os << std::hex << i;
    }
    return os;
}

class oath_initialiser
{
private:
    oath_initialiser()
    {
        auto result = oath_init();
        if ( result != OATH_OK )
        {
            std::stringstream err;
            err << "oath_init() failed with: "
                << oath_strerror_name(result) << " (" << result << ") " << oath_strerror(result);
            throw std::runtime_error(err.str());
        }
    }
public:
    ~oath_initialiser()
    {
        auto result = oath_done();
        if ( result != OATH_OK )
        {
            std::stringstream err;
            std::cout << "oath_done() failed with: "
                      << oath_strerror_name(result) << " (" << result << ") " << oath_strerror(result)
                      << std::endl;
        }
    }
    static std::shared_ptr<oath_initialiser> get()
    {
        static std::shared_ptr<oath_initialiser> singleton(new oath_initialiser());
        return singleton;
    }
};

bytes_type b32d(const std::string& input)
{
    char* decoded;
    size_t decoded_size = 0;
    auto result = oath_base32_decode(input.data(), input.size(), &decoded, &decoded_size);
    std::unique_ptr<char[]> safe_decoded(decoded);
    if ( result != OATH_OK )
    {
        std::stringstream err;
        err << "oath_base32_decode(\"" << input << "\", " << input.size() << ", _, _) failed with: "
            << oath_strerror_name(result) << " (" << result << ") " << oath_strerror(result);
        throw std::runtime_error(err.str());
    }
    return bytes_type(decoded, decoded+decoded_size);
}
std::string b32e(const uint8_t* data, size_t data_size)
{
    char* encoded;
    size_t encoded_size = 0;
    auto result = oath_base32_encode(reinterpret_cast<const char*>(data), data_size, &encoded, &encoded_size);
    std::unique_ptr<char[]> safe_encoded(encoded);
    if ( result != OATH_OK )
    {
        std::stringstream err;
        err << "oath_base32_encode(\"" << data << "\", " << data_size << ", _, _) failed with: "
            << oath_strerror_name(result) << " (" << result << ") " << oath_strerror(result);
        throw std::runtime_error(err.str());
    }
    return std::string(encoded, encoded+encoded_size);
}

}


int main(int argc, char* argv[])
{
    auto oath_init = oath_initialiser::get();
    handle_options(argc, argv);

    bytes_type data = { 0x61, 0x62, 0x63, 0x64 };
    std::cout << "data: " << data << std::endl;

    std::string jimmy = "NJUW23LZBI===";
    auto res = b32d(jimmy);
    std::cout << "res: " << res << std::endl;

    auto rese = b32e(res.data(), res.size());
    std::cout << "rese: " << rese << std::endl;
    return 0;
}