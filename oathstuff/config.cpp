#include "config.hpp"

#include <cstdlib>
#include <cstdio>
#include <fcntl.h>

#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/writer.h>

namespace {
const char* env_home = std::getenv("HOME");
const std::string user_config_dir_path_prefix = env_home ? env_home : ".";
const std::string user_config_dir_path = user_config_dir_path_prefix + "/.otps";
const std::string user_keys_file_path = user_config_dir_path + "/keys";
}

config_file::config_file() :
    user_keys_path_(user_keys_file_path)
{
    init();
}
const keys_data_type& config_file::read_keys()
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
void config_file::append_keys(keys_data_type keys)
{
    keys.insert(keys.end(), keys_.begin(), keys_.end());
    save_keys(keys);
}
void config_file::save_keys(keys_data_type keys)
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
void config_file::init()
{
    auto keys_status = std::filesystem::status(user_keys_path_);
    if ( ! std::filesystem::exists(keys_status) ) return; // no keys file, fair enough
    validate_key_file(keys_status);
}
void config_file::validate_key_file(const std::filesystem::file_status& status)
{
    if ( ! std::filesystem::is_regular_file(status) ) throw std::runtime_error("keys file is not regular file");
    auto keys_perms = status.permissions();
    if ( ( keys_perms & ( std::filesystem::perms::group_all |
                          std::filesystem::perms::others_all ) )
             != std::filesystem::perms::none ) throw std::runtime_error("keys file incorrect perms");
}
