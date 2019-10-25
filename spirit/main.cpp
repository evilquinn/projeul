#include <boost/spirit/include/qi.hpp>
#include <string>
#include <boost/optional.hpp>
#include <iostream>
#include <vector>

template <typename Iterator>
struct sku_grammar : boost::spirit::qi::grammar<Iterator,
                                                boost::optional<std::string>()>
{
    sku_grammar() : sku_grammar::base_type{ra_text}
    {
        text %= +(boost::spirit::ascii::char_ - ']');
        opt_text %= -text;
        ra_text %= '[' >> opt_text >> ']';
    }

    boost::spirit::qi::rule<Iterator, std::string()> text;
    boost::spirit::qi::rule<Iterator, boost::optional<std::string>()> opt_text;
    boost::spirit::qi::rule<Iterator, boost::optional<std::string>()> ra_text;
};

int main()
{
    std::string s = "[]";
    std::vector<std::string> inputs = {
        "[]",
        "[ra_text]",
        "[[[[text]"
        "[[[[text]]]"
    };

    for ( auto&& s : inputs )
    {
        std::cout << s << " -> ";
        auto it = s.begin();
        sku_grammar<std::string::iterator> h;
        boost::optional<std::string> result;
        if (boost::spirit::qi::parse(it, s.end(), h, result))
        {
            std::cout << (result ? *result : std::string("empty")) << std::endl;
        }
        else
        {
            std::cout << "no match" << std::endl;
        }
    }
}
