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

typedef std::vector<std::string> list_matcher_type;
typedef std::vector<list_matcher_type> distinct_matcher_type;
class matcher;
typedef std::map<std::string, matcher> matcher_registry_type;
class matcher
{
public:
    matcher(){}
    explicit matcher(const matcher_registry_type& registry) :
        registry_(&registry)
    {
        matchers_.push_back(list_matcher_type());
    }
    void start_alternative()
    {
        if ( ! literal_.empty() ) throw std::runtime_error("Cannot add matcher to matcher already set with literal");
        matchers_.push_back(list_matcher_type());
    }
    void add_matcher(std::string_view matcher)
    {
        if ( ! literal_.empty() ) throw std::runtime_error("Cannot add matcher to matcher already set with literal");
        matchers_.back().push_back(std::string(matcher));
    }
    void set_literal(std::string_view literal)
    {
        for ( auto&& matcher_list : matchers_ )
        {
            for ( auto&& dummy : matcher_list )
            {
                (void)dummy;
                throw std::runtime_error("Cannot set literal on matcher with other matchers already set");
            }
        }
        literal_ = literal;
    }
    bool test(std::string_view sample) const
    {
        return match(sample) == sample.size();
    }
private:
    size_t match(std::string_view sample) const
    {
        if ( ! literal_.empty() )
        {
            return match_literal(sample);
        }
        return match_matchers(sample);
    }
    size_t match_literal(std::string_view sample) const
    {
        return boost::algorithm::starts_with(sample, literal_) ? literal_.size() : 0;
    }
    size_t match_matchers(std::string_view sample) const
    {
        for ( auto&& matcher_list : matchers_ )
        {
            size_t res = match_list(sample, matcher_list);
            if ( res > 0 )
            {
                return res;
            }
        }
        return 0;
    }
    size_t match_list(std::string_view sample, list_matcher_type matcher_list) const
    {
        size_t pos = 0;
        size_t matcher_idx = 0;
        while ( pos < sample.size() && matcher_idx < matcher_list.size() )
        {
            size_t match = registry_->at(matcher_list[matcher_idx]).match(sample.substr(pos));
            if ( match == 0 ) break;
            pos += match;
            ++matcher_idx;
        }
        return matcher_idx == matcher_list.size() ? pos : 0;
    }
    const matcher_registry_type* registry_;
    std::string literal_;
    distinct_matcher_type matchers_;
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
        return registry_.at("0").test(sample);
    }
    void update_rule(const std::string& rule_id, std::string_view hack)
    {
        auto&& rule = rules_[rule_id];
        rule = hack;
        registry_[rule_id] = parse_rule(rule);
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

        for ( auto&& rule : rules_ )
        {
            registry_[rule.first] = parse_rule(rule.second);
        }
    }

    matcher parse_rule(std::string_view rule)
    {
        matcher result(registry_);
        size_t part_begin = 0;
        while ( part_begin < rule.size() )
        {
            switch ( rule[part_begin] )
            {
            case '"' : /* it's a literal */
            {
                ++part_begin;
                size_t part_end = rule.find('"', part_begin);
                result.set_literal(rule.substr(part_begin, part_end - part_begin));
                part_begin = rule.find_first_not_of(' ', part_end + 1 );
                break;
            }
            case '|' :
            {
                result.start_alternative();
                part_begin = rule.find_first_not_of(' ', part_begin + 1 );
                break;
            }
            case ' ' : throw 42;              break;
            default  : /* it's a rule id reference */
            {
                size_t part_end = rule.find(' ', part_begin);
                result.add_matcher(rule.substr(part_begin, part_end - part_begin));
                part_begin = rule.find_first_not_of(' ', part_end);
                break;
            }
            }
        }
        return result;
    }
    std::map<std::string, std::string> rules_;
    matcher_registry_type registry_;
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
        if ( rulio.test(sample) )
        {
            std::cout << sample << std::endl;
            ++result;
        }
    }
    std::cout << "result: " << result << std::endl;
#endif

    return 0;
}
