#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
#include <boost/algorithm/string.hpp>

// interprets a value and inserts _something_ into the ptree
// at the specified path
typedef boost::function<void(boost::property_tree::ptree&,
                             const std::string&,
                             const std::string&)> ptree_inserter;

// describes how to update a path in a ptree
struct inserter_rule
{
    std::string path;
    ptree_inserter inserter;
};

// maps a string to a rule
typedef std::map<std::string, struct inserter_rule> rules_map;

// puts a value into a ptree
// converts to template type
template <typename ToType>
class value_inserter
{
public:
    void operator()(boost::property_tree::ptree& pt,
                    const std::string& path,
                    const std::string& value)
    {
        pt.put(path, boost::lexical_cast<ToType>(value));
    }
};

// interprets a value as a comma-delimited string list and inserts
// a ptree containing name and charArray nodes into an array of nodes
// at the supplied path
class custom_array_inserter
{
public:
    custom_array_inserter(const std::string& array_key)
    :
        array_key_(array_key)
    {}
    void operator()(boost::property_tree::ptree& pt,
                    const std::string& path,
                    const std::string& value)
    {
        boost::property_tree::ptree child_list;
        try
        {
            child_list = pt.get_child(path);
        }
        catch(const std::exception& ex)
        {
            child_list = pt.add_child(path, boost::property_tree::ptree());
        }
        boost::property_tree::ptree child;
        child.put("name", array_key_);
        boost::property_tree::ptree array_node;
        std::vector<std::string> vals;
        boost::split(vals, value, boost::is_any_of(","));
        for ( auto&& val : vals )
        {
            boost::property_tree::ptree el;
            boost::algorithm::trim_left(val);
            el.put("", val);
            array_node.push_back(std::make_pair("", el));
        }
        child.put_child("charArrays", array_node);
        child_list.push_back(std::make_pair("", child));
        pt.put_child(path, child_list);
    }
private:
    std::string array_key_;
};

int main()
{
    // configure rules upfront, map a string to an insertion rule
    rules_map rules;
    rules["setting1"] = inserter_rule{ "top.sub.leaf.node", value_inserter<int>() };
    rules["setting2"] = inserter_rule{ "top.sub.leaf2.int_flag", value_inserter<int>() };
    rules["setting3"] = inserter_rule{ "top.sub.leaf2.bool_flag", value_inserter<bool>() };
    rules["setting4"] = inserter_rule{ "top.sub.leaf3.node", value_inserter<std::string>() };
    rules["setting5"] = inserter_rule{ "top.sub2.node", custom_array_inserter("MY_array_key") };
    rules["setting6"] = inserter_rule{ "top.sub2.node", custom_array_inserter("second_array_key") };

    // configure the optional settings to handle
    std::map<std::string, std::string> optional_settings;
    optional_settings["setting1"] = "4";
    optional_settings["setting2"] = "1";
    optional_settings["setting3"] = "0";
    optional_settings["setting4"] = "the_value";
    optional_settings["setting5"] = "first, second, third";
    optional_settings["setting6"] = "niall, is, super";

    // handle optional settings
    boost::property_tree::ptree setdog;
    for ( auto&& optional_setting : optional_settings )
    {
        auto rule = rules.find(optional_setting.first);
        if ( rule != rules.end() )
        {
            rule->second.inserter(setdog, rule->second.path, optional_setting.second);
        }
    }

    // dump
    boost::property_tree::json_parser::write_json(std::cout, setdog);
    return 0;
}
