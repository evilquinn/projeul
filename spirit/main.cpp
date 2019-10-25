#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <boost/optional.hpp>
#include <iostream>
#include <vector>

struct c_text_data
{
    char colour;
    boost::optional<std::string> opt_text;
};

std::ostream& operator<< (std::ostream& os, const struct c_text_data& c)
{
    os << "colour: " << c.colour;
    if ( c.opt_text )
    {
        os << ", text: \"" << *c.opt_text << "\"";
    }
    return os;
}

BOOST_FUSION_ADAPT_STRUCT(
    c_text_data,
    (char, colour)
    (boost::optional<std::string>, opt_text)
)

typedef boost::optional<std::string> optional_text;
typedef boost::variant<optional_text, c_text_data> opt_or_c_text;

template <typename Iterator>
struct sku_grammar : boost::spirit::qi::grammar<Iterator,
                                                c_text_data()>
{
    sku_grammar() : sku_grammar::base_type{c_text}
    {
        text %= +( ( boost::spirit::ascii::char_ - ']') - ')' );
        opt_text %= -text;
        c_text %= '_' >> boost::spirit::ascii::char_ >> '(' >> opt_text >> ')';
        ra_text %= '[' >> opt_text >> ']';

    }

    boost::spirit::qi::rule<Iterator, std::string()> text;
    boost::spirit::qi::rule<Iterator, boost::optional<std::string>()> opt_text;
    boost::spirit::qi::rule<Iterator, c_text_data()> c_text;
    boost::spirit::qi::rule<Iterator, boost::optional<std::string>()> ra_text;
    //boost::spirit::qi::rule<Iterator, boost::optional<std::string>()> ra_text;
};

int main()
{
    std::vector<std::string> inputs = {
        "[]",
        "_r()",
        "[_r()]",
        "[ra_text]",
        "[[[[text]",
        "_w(jimmy)",
        "[[[[text]]]"
    };

    for ( auto&& s : inputs )
    {
        std::cout << s << " -> ";
        auto it = s.begin();
        sku_grammar<std::string::iterator> h;
        boost::optional<std::string> result;
        c_text_data c_result;
        if (boost::spirit::qi::parse(it, s.end(), h, c_result))
        {
            std::cout << "matched: " << c_result;
//            std::cout << "matched";
//            if ( result )
//            {
//                std::cout << ": text: \"" << *result << "\"";
//            }
            if ( it != s.end() )
            {
                std::cout << ", remaining: \""
                          << std::string(it, s.end()) << "\"";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "no match" << std::endl;
        }
    }
}
