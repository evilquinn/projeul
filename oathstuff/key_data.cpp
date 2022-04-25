#include "key_data.hpp"
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>

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
