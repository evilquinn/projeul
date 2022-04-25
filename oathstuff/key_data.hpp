#ifndef PROJEUL_OATHSTUFF_KEY_DATA_HPP
#define PROJEUL_OATHSTUFF_KEY_DATA_HPP

#include <vector>
#include <string>
#include <rapidjson/fwd.h>
#include <rapidjson/writer.h>
#include <boost/algorithm/hex.hpp>

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
    key_data(std::string id) :
        id(id)
    {}
    key_data(std::string id, std::vector<uint8_t> key) :
        id(id),
        key(key)
    {}
};

template<typename WriterTs>
rapidjson::Writer<WriterTs>& operator<< (rapidjson::Writer<WriterTs>& rjw, const struct key_data& data)
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

std::ostream& operator<< (std::ostream& os, const struct key_data& data);
rapidjson::Value& operator>> (rapidjson::Value& json_in, struct key_data& data);

typedef std::vector<key_data> keys_data_type;

template<typename WriterTs>
rapidjson::Writer<WriterTs>& operator<< (rapidjson::Writer<WriterTs>& rjw, const keys_data_type& data)
{
    rjw.StartArray();
    for ( auto&& key : data )
    {
        rjw << key;
    }
    rjw.EndArray();
    return rjw;
}

rapidjson::Value& operator>> (rapidjson::Value& json_in, keys_data_type& data);

#endif // PROJEUL_OATHSTUFF_KEY_DATA_HPP
