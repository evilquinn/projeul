#include <iostream>
#include <vector>

#include <boost/utility/string_view.hpp>
#include <boost/function.hpp>

typedef boost::function<size_t(boost::string_view)> matcher_type;
struct string_matcher
{
    string_matcher(const std::string& literal) :
        literal_(literal)
    {}
    size_t operator()(boost::string_view sample)
    {
        return sample.starts_with(literal_) ? literal_.size() : 0;
    }
private:
    std::string literal_;
};
struct or_matcher
{
    or_matcher(const matcher_type& matcher) :
        matchers_()
    {
        matchers_.push_back(matcher);
    }
    void or_match(const matcher_type& matcher)
    {
        matchers_.push_back(matcher);
    }
    size_t operator()(boost::string_view sample)
    {
        for ( const matcher_type& matcher : matchers_ )
        {
            size_t res = matcher(sample);
            if ( res > 0 )
            {
                return res;
            }
        }
        return 0;
    }
private:
    std::vector<matcher_type> matchers_;
};
struct sequential_matcher
{
    sequential_matcher(const matcher_type& matcher)
    {
        matchers_.push_back(matcher);
    }
    void then_match(const matcher_type& matcher)
    {
        matchers_.push_back(matcher);
    }
    size_t operator() (boost::string_view sample)
    {
        size_t pos = 0;
        size_t matcher_idx = 0;
        while ( pos <= sample.size() && matcher_idx < matchers_.size() )
        {
            pos += matchers_[matcher_idx](sample.substr(pos));
            ++matcher_idx;
        }
        return pos == sample.size() ? pos : 0;
    }
private:
    std::vector<matcher_type> matchers_;
};

int main()
{
    string_matcher one("a");
    string_matcher three("b");
    sequential_matcher two_a(one); two_a.then_match(three);
    sequential_matcher two_b(three); two_b.then_match(one);
    or_matcher two(two_a); two.or_match(two_b);
    sequential_matcher zero(one); zero.then_match(two);

    std::vector<std::string> samples =
    {
        "aaa",
        "aab",
        "aba",
        "baa",
        "abb",
        "bba",
        "bbb"
    };

    for ( auto&& sample : samples )
    {
        if ( zero(sample) == sample.size() )
        {
            std::cout << sample << " : MATCHES" << std::endl;
        }
        else
        {
            std::cout << sample << " : FAILS" << std::endl;
        }
    }

    return 0;
}
