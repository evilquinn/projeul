/**
 * meh
 *
 **/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

class nanofactory
{
public:
    typedef std::pair<std::string, int> chem_type;
    typedef std::map<std::string, int> chem_list;
    typedef std::pair<chem_type, chem_list> rule_type;
    typedef std::map<std::string, rule_type> rules_type;
    friend std::ostream& operator<< (std::ostream& os, const nanofactory& nf);
    nanofactory(std::istream& rulestream) :
        rules_(parse_rules(rulestream))
    {}
    nanofactory(const std::string& rulestring) :
        rules_(parse_rules(rulestring))
    {}
    int calc_ore_for(int quantity, const std::string& target)
    {
        int result = 0;

        chem_list cauldron;
        cauldron[target] = quantity;
        chem_list distilled;

        // keep going until we've only got ORE
        while ( ! cauldron.empty() )
        {
            auto it = cauldron.begin();
            if ( it == cauldron.end() )
            {
                throw std::runtime_error(std::string("couldn't find non-ORE chemical in cauldron"));
            }
            // find the rule to make it
            auto it_rule = rules_.find(it->first);
            if ( it_rule == rules_.end() )
            {
                throw std::runtime_error(std::string("couldn't find rule to make chem: " + it->first));
            }
            if ( it_rule->second.second.count("ORE") > 0 )
            {
                // distilled
                distilled[it->first] += it->second;
                cauldron.erase(it);
            }
            else
            {
                int mult = ( it->second / it_rule->second.first.second );
                if ( it->second % it_rule->second.first.second ) ++mult;
                cauldron.erase(it);
                for ( auto&& chem : it_rule->second.second )
                {
                    cauldron[chem.first] += ( mult * chem.second);
                }
            }
        }
        for ( auto&& chem : distilled )
        {
            // find the rule to make it
            auto it_rule = rules_.find(chem.first);
            if ( it_rule == rules_.end() )
            {
                throw std::runtime_error(std::string("couldn't find rule to make chem: " + chem.first));
            }
            if ( it_rule->second.second.count("ORE") == 0 || it_rule->second.second.size() != 1 )
            {
                throw std::runtime_error(std::string("couldn't find ORE rule for chem: " + chem.first));
            }
            else
            {
                int mult = ( chem.second / it_rule->second.first.second );
                if ( chem.second % it_rule->second.first.second ) ++mult;
                result += mult * it_rule->second.second["ORE"];
            }
        }


        return result;
    }
private:

    rules_type parse_rules(std::istream& rulestream)
    {
        rules_type result;
        std::string rule_str;
        while( std::getline(rulestream, rule_str) )
        {
            auto rule = parse_rule(rule_str);
            result.insert({ rule.first.first, rule });
        }
        return result;
    }
    rules_type parse_rules(const std::string& rulestring)
    {
        std::stringstream ss(rulestring);
        return parse_rules(ss);
    }
    rule_type parse_rule(const std::string& rule)
    {
        rule_type result;
        auto beg = rule.begin();
        auto cl = parse_chem_list(beg, rule.end());
        auto cr = parse_chem_type(beg, rule.end());
        result.first = cr;
        result.second = cl;
        return result;
    }
    chem_list parse_chem_list(std::string::const_iterator& beg, const std::string::const_iterator& end)
    {
        chem_list result;
        do
        {
            auto chem = parse_chem_type(beg, end);
            result[chem.first] = chem.second;
        } while ( *beg == ',' );
        return result;
    }
    chem_type parse_chem_type(std::string::const_iterator& beg, const std::string::const_iterator& end)
    {
        const std::string delims = ", =>";
        beg = std::find_if_not(beg, end, [&delims](const std::string::value_type& v)
              {
                  return std::find(delims.begin(), delims.end(), v) != delims.end();
              });
        auto delim = std::find_first_of(beg, end, delims.begin(), delims.end());
        auto quantity = boost::lexical_cast<int>(&*beg, std::distance(beg, delim));
        beg = ++delim;
        delim = std::find_first_of(beg, end, delims.begin(), delims.end());
        std::string symbol(beg, delim);
        beg = delim;
        return { symbol, quantity };
    }
    rules_type rules_;
};
std::ostream& operator<< (std::ostream& os, const nanofactory& nf)
{
    std::string nl_sep = "";
    for ( auto&& rule : nf.rules_ )
    {
        std::string comma_sep = "";
        os << nl_sep;
        for ( auto&& chem : rule.second.second )
        {
            os << comma_sep << chem.first << " " << chem.second;
            comma_sep = ", ";
        }
        nl_sep = "\n";
        os << " => " << rule.second.first.first << " " << rule.second.first.second;
    }
    return os;
}


int main()
{

    std::vector<std::string> data = {
/*
        "10 ORE => 10 A\n"
        "1 ORE => 1 B\n"
        "7 A, 1 B => 1 C\n"
        "7 A, 1 C => 1 D\n"
        "7 A, 1 D => 1 E\n"
        "7 A, 1 E => 1 FUEL",

        "9 ORE => 2 A\n"
        "8 ORE => 3 B\n"
        "7 ORE => 5 C\n"
        "3 A, 4 B => 1 AB\n"
        "5 B, 7 C => 1 BC\n"
        "4 C, 1 A => 1 CA\n"
        "2 AB, 3 BC, 4 CA => 1 FUEL",

        "157 ORE => 5 NZVS\n"
        "165 ORE => 6 DCFZ\n"
        "44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL\n"
        "12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"
        "179 ORE => 7 PSHF\n"
        "177 ORE => 5 HKGWZ\n"
        "7 DCFZ, 7 PSHF => 2 XJWVT\n"
        "165 ORE => 2 GPVTF\n"
        "3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT\n",
*/
        "2 VPVL, 7 FWMGM, 2 CXFTF, 11 MNCFX => 1 STKFG\n"
        "17 NVRVD, 3 JNWZP => 8 VPVL\n"
        "53 STKFG, 6 MNCFX, 46 VJHF, 81 HVMC, 68 CXFTF, 25 GNMV => 1 FUEL\n"
        "22 VJHF, 37 MNCFX => 5 FWMGM\n"
        "139 ORE => 4 NVRVD\n"
        "144 ORE => 7 JNWZP\n"
        "5 MNCFX, 7 RFSQX, 2 FWMGM, 2 VPVL, 19 CXFTF => 3 HVMC\n"
        "5 VJHF, 7 MNCFX, 9 VPVL, 37 CXFTF => 6 GNMV\n"
        "145 ORE => 6 MNCFX\n"
        "1 NVRVD => 8 CXFTF\n"
        "1 VJHF, 6 MNCFX => 4 RFSQX\n"
        "176 ORE => 6 VJHF\n",

        "171 ORE => 8 CNZTR\n"
        "7 ZLQW, 3 BMBT, 9 XCVML, 26 XMNCP, 1 WPTQ, 2 MZWV, 1 RJRHP => 4 PLWSL\n"
        "114 ORE => 4 BHXH\n"
        "14 VRPVC => 6 BMBT\n"
        "6 BHXH, 18 KTJDG, 12 WPTQ, 7 PLWSL, 31 FHTLT, 37 ZDVW => 1 FUEL\n"
        "6 WPTQ, 2 BMBT, 8 ZLQW, 18 KTJDG, 1 XMNCP, 6 MZWV, 1 RJRHP => 6 FHTLT\n"
        "15 XDBXC, 2 LTCX, 1 VRPVC => 6 ZLQW\n"
        "13 WPTQ, 10 LTCX, 3 RJRHP, 14 XMNCP, 2 MZWV, 1 ZLQW => 1 ZDVW\n"
        "5 BMBT => 4 WPTQ\n"
        "189 ORE => 9 KTJDG\n"
        "1 MZWV, 17 XDBXC, 3 XCVML => 2 XMNCP\n"
        "12 VRPVC, 27 CNZTR => 2 XDBXC\n"
        "15 KTJDG, 12 BHXH => 5 XCVML\n"
        "3 BHXH, 2 VRPVC => 7 MZWV\n"
        "121 ORE => 7 VRPVC\n"
        "7 XCVML => 6 RJRHP\n"
        "5 BHXH, 4 VRPVC => 5 LTCX\n"
    };

    for ( auto&& datum : data )
    {
        std::stringstream ss(datum);
        nanofactory nf(ss);
        auto result = nf.calc_ore_for(1, "FUEL");
        std::cout << "nf:\n" << nf << "\nresult: " << result << "\n\n";
    }

    return 0;
}
