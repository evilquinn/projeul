#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <string>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <vector>

struct c_text_data
{
    char colour;
    boost::optional<std::string> opt_text;
};

typedef boost::optional<std::string> optional_text;
typedef boost::variant<optional_text, c_text_data> opt_or_c_text;

std::ostream& operator<< (std::ostream& os, const struct c_text_data& c)
{
    os << "colour: " << c.colour;
    if ( c.opt_text )
    {
        os << ", text: \"" << *c.opt_text << "\"";
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const optional_text& opt)
{
    if ( opt )
    {
        os << ", text: \"" << *opt << "\"";
    }
    return os;
}

class opt_or_c_printer : public boost::static_visitor<>
{
public:
    opt_or_c_printer(std::ostream& os) : os_(os) {}
    template <typename T>
    void operator()(const T& t) const
    {
        os_ << t;
    }
private:
    std::ostream& os_;
};

std::ostream& operator<<(std::ostream& os, const opt_or_c_text& g)
{
    opt_or_c_printer p(os);
    boost::apply_visitor(p, g);
    return os;
}

BOOST_FUSION_ADAPT_STRUCT(
    c_text_data,
    (char, colour)
    (boost::optional<std::string>, opt_text)
)


template <typename Iterator>
struct sku_grammar : boost::spirit::qi::grammar<Iterator,
                                                opt_or_c_text()>
{
    sku_grammar() : sku_grammar::base_type{either_or}
    {
        text %= +( ( boost::spirit::ascii::char_ - ']') - ')' );
        opt_text %= -text;
        c_text %= '_' >> boost::spirit::ascii::char_ >> '(' >> opt_text >> ')';
        ra_text %= '[' >> opt_text >> ']';
        either_or %= c_text | ra_text;

    }

    boost::spirit::qi::rule<Iterator, std::string()> text;
    boost::spirit::qi::rule<Iterator, boost::optional<std::string>()> opt_text;
    boost::spirit::qi::rule<Iterator, c_text_data()> c_text;
    boost::spirit::qi::rule<Iterator, boost::optional<std::string>()> ra_text;
    boost::spirit::qi::rule<Iterator, opt_or_c_text()> either_or;
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
        opt_or_c_text o_result;
        if (boost::spirit::qi::parse(it, s.end(), h, o_result))
        {
            std::cout << "matched: " << o_result;
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
