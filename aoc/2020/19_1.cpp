#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string_view>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/function.hpp>

#include <aoc/path_def.hpp>

namespace aoc
{

typedef boost::function<size_t(std::string_view)> matcher_type;
struct string_matcher
{
    explicit string_matcher(std::string literal) :
        literal_(literal)
    {}
    size_t operator()(std::string_view sample)
    {
        return boost::algorithm::starts_with(sample, literal_) ? literal_.size() : 0;
    }
private:
    std::string literal_;
};
struct or_matcher
{
    or_matcher()
    {}
    explicit or_matcher(const matcher_type& matcher) :
        matchers_()
    {
        matchers_.push_back(matcher);
    }
    or_matcher& or_match(const matcher_type& matcher)
    {
        matchers_.push_back(matcher);
        return *this;
    }
    size_t operator()(std::string_view sample)
    {
        for ( auto&& matcher : matchers_ )
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
    sequential_matcher()
    {}
    explicit sequential_matcher(const matcher_type& matcher)
    {
        matchers_.push_back(matcher);
    }
    sequential_matcher& then_match(const matcher_type& matcher)
    {
        matchers_.push_back(matcher);
        return *this;
    }
    size_t operator() (std::string_view sample)
    {
        size_t pos = 0;
        size_t matcher_idx = 0;
        while ( pos < sample.size() && matcher_idx < matchers_.size() )
        {
            size_t match = matchers_[matcher_idx](sample.substr(pos));
            if ( match == 0 ) break;
            pos += match;
            ++matcher_idx;
        }
        return matcher_idx == matchers_.size() ? pos : 0;
    }
private:
    std::vector<matcher_type> matchers_;
};

class message_rules
{
public:
    explicit message_rules(std::istream& is)
    {
        parse_rules(is);
    }
    bool test(std::string_view sample)
    {
        return matcher_(sample) == sample.size();
    }

private:
    void parse_rules(std::istream& is)
    {
        std::string line;
        while ( std::getline(is, line) )
        {
            if ( line.empty() ) break;
            std::string_view rule_id(line.data(), line.find(':'));
            size_t rule_part_begin = line.find_first_not_of(' ', rule_id.size() + 1);
            rules_[std::string(rule_id)] = line.substr(rule_part_begin, line.size() - rule_part_begin);
        }

        matcher_ = parse_matcher("0");
    }

    matcher_type& parse_matcher(std::string_view rule_id)
    {
        if ( matchers_.count(rule_id) > 0 ) return matchers_[rule_id];

        std::string_view rule = rules_[std::string(rule_id)];
        size_t part_begin = 0;
        bool saw_or = false;
        or_matcher orer;
        sequential_matcher current;
        while ( part_begin < rule.size() )
        {
            switch ( rule[part_begin] )
            {
            case '"' : /* it's a literal */
            {
                ++part_begin;
                size_t part_end = rule.find('"', part_begin);
                current.then_match(string_matcher(std::string(rule.substr(part_begin, part_end - part_begin))));
                part_begin = rule.find_first_not_of(' ', part_end + 1 );
                break;
            }
            case '|' :
            {
                orer.or_match(current);
                current = sequential_matcher();
                saw_or = true;
                part_begin = rule.find_first_not_of(' ', part_begin + 1 );
                break;
            }
            case ' ' : throw 42;              break;
            default  : /* it's a rule id reference */
            {
                size_t part_end = rule.find(' ', part_begin);
                matcher_type& part_matcher = parse_matcher(rule.substr(part_begin, part_end - part_begin));
                current.then_match(part_matcher);
                part_begin = rule.find_first_not_of(' ', part_end);
                break;
            }
            }
        }
        if ( saw_or )
        {
            orer.or_match(current);
            matchers_[rule_id] = orer;
        }
        else
        {
            matchers_[rule_id] = current;
        }

        return matchers_[rule_id];
    }
    matcher_type matcher_;
    std::map<std::string, std::string> rules_;
    std::map<std::string_view, matcher_type> matchers_;
};

} // end namespace aoc

int main()
{
#if 0
    auto one = aoc::string_matcher("a");
    auto three = aoc::string_matcher("b");
    auto two_a = aoc::sequential_matcher(one).then_match(three);
    auto two_b = aoc::sequential_matcher(three).then_match(one);
    auto two = aoc::or_matcher(two_a).or_match(two_b);
    auto zero = aoc::sequential_matcher(one).then_match(two);

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
#endif
#if 0

    typedef std::vector<std::pair<std::string, bool> > samples_type;
    typedef std::vector<std::pair<std::string, samples_type> > tests_type;
    tests_type tests =
    {
        { "0: 1 2\n1: \"a\"\n2: 1 3 | 3 1\n3: \"b\"",
          { { "aaa", false },
            { "aab", true  },
            { "aba", true  },
            { "baa", false },
            { "abb", false },
            { "bba", false },
            { "bbb", false } } },
        { "0: 4 1 5\n1: 2 3 | 3 2\n2: 4 4 | 5 5\n3: 4 5 | 5 4\n4: \"a\"\n5: \"b\"",
          { { "aaaabb", true  },
            { "aaabab", true  },
            { "abbabb", true  },
            { "abbbab", true  },
            { "aabaab", true  },
            { "aabbbb", true  },
            { "abaaab", true  },
            { "baabab", false },
            { "abbaba", false },
            { "abbbbb", false },
            { "bbbbab", false },
            { "ababbb", true  } } }
    };

    for ( auto&& test : tests )
    {
        std::cout << "Rule:\n" << test.first << std::endl;
        std::istringstream input(test.first);
        aoc::message_rules r(input);
        auto&& samples = test.second;
        for ( auto&& sample : samples )
        {
            std::cout << "Testing: " << sample.first
                    << ", expected: " << sample.second
                    << ", actual: " << r.test(sample.first)
                    << std::endl;
        }
        std::cout << std::endl;
    }

#endif

#if 1
    std::ifstream input_file( PROJEUL_AOC_PATH "/19_input.txt" );
    aoc::message_rules rulio(input_file);
    size_t result = 0;
    std::string sample;
    while ( std::getline(input_file, sample) )
    {
        if ( rulio.test(sample) ) ++result;
    }
    std::cout << "result: " << result << std::endl;
#endif

    return 0;
}
