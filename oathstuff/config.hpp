#ifndef PROJEUL_OATHSTUFF_CONFIG_HPP
#define PROJEUL_OATHSTUFF_CONFIG_HPP

#include <filesystem>
#include "key_data.hpp"

class config_file
{
public:
    config_file();
    const keys_data_type& read_keys();
    void append_keys(keys_data_type keys);
    void save_keys(keys_data_type keys);
private:
    void init();
    void validate_key_file(const std::filesystem::file_status& status);
    std::filesystem::path user_keys_path_;
    keys_data_type keys_;
};

#endif // PROJEUL_OATHSTUFF_CONFIG_HPP
