/**
 * meh
 *
 **/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

typedef std::pair<std::string, size_t> chem_type;
typedef std::map<std::string, size_t> chem_list;
typedef std::pair<chem_type, chem_list> rule_type;
typedef std::map<std::string, rule_type> rules_type;

std::ostream& operator<< (std::ostream& os, const chem_list& cl)
{
    std::string sep = "";
    for ( auto&& chem : cl )
    {
        os << sep << chem.first << " " << chem.second;
        sep = ", ";
    }
    return os;
}
class nanofactory
{
public:
    friend std::ostream& operator<< (std::ostream& os, const nanofactory& nf);
    nanofactory(std::istream& rulestream) :
        rules_(parse_rules(rulestream))
    {}
    nanofactory(const std::string& rulestring) :
        rules_(parse_rules(rulestring))
    {}
    size_t calc_ore_for(size_t quantity, const std::string& target_name)
    {
        chem_list cauldron;
        cauldron[target_name] = quantity;
        chem_list spares;

        // keep going until we've only got ORE
        while ( ! ( cauldron.size() == 1 && cauldron.count("ORE") == 1 ) )
        {
            auto target_it = cauldron.begin();
            while ( target_it != cauldron.end() && target_it->first == "ORE" )
            {
                std::advance(target_it, 1);
            }
            if ( target_it == cauldron.end() )
            {
                throw std::runtime_error(std::string("couldn't find non-ORE chemical in cauldron"));
            }
            chem_type target = *target_it;
            cauldron.erase(target_it);

            // first check if we've got anything in spares
            if ( spares.count(target.first) > 0 )
            {
                if ( spares[target.first] >= target.second )
                {
                    // don't need to manufacture, satisfy from spares
                    spares[target.first] -= target.second;
                    if ( spares[target.first] == 0 ) spares.erase(target.first);
                    target.second = 0;
                    continue;
                }
                else if ( spares[target.first] < target.second )
                {
                    target.second -= spares[target.first];
                    spares.erase(target.first);
                }
            }

            // find the rule to make it
            auto target_rule_it = rules_.find(target.first);
            if ( target_rule_it == rules_.end() )
            {
                throw std::runtime_error(std::string("couldn't find rule to make chem: " + target.first));
            }
            rule_type target_rule = target_rule_it->second;

            // how many rule applications needed to satisfy?
            while ( target.second > 0 )
            {
                for ( auto rule_chem : target_rule.second )
                {
                    cauldron[rule_chem.first] += rule_chem.second;
                }
                if ( target_rule.first.second < target.second )
                {
                    // not yet satisfied
                    target.second -= target_rule.first.second;
                }
                else
                {
                    // entirely satisfied, deal with spares
                    size_t remaining = target_rule.first.second - target.second;
                    target.second = 0;
                    if ( remaining > 0 ) spares[target.first] += remaining;
                }
            }
        }
        return cauldron["ORE"];
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
        auto quantity = boost::lexical_cast<size_t>(&*beg, std::distance(beg, delim));
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
        os << nl_sep << rule.second.second;
        os << " => " << rule.second.first.first << " " << rule.second.first.second;
        nl_sep = "\n";
    }
    return os;
}


int main()
{

    std::vector<std::pair<std::string, size_t> > data = {

        { "10 ORE => 10 A\n"
          "1 ORE => 1 B\n"
          "7 A, 1 B => 1 C\n"
          "7 A, 1 C => 1 D\n"
          "7 A, 1 D => 1 E\n"
          "7 A, 1 E => 1 FUEL", 31 },

        { "9 ORE => 2 A\n"
          "8 ORE => 3 B\n"
          "7 ORE => 5 C\n"
          "3 A, 4 B => 1 AB\n"
          "5 B, 7 C => 1 BC\n"
          "4 C, 1 A => 1 CA\n"
          "2 AB, 3 BC, 4 CA => 1 FUEL", 165 },

        { "157 ORE => 5 NZVS\n"
          "165 ORE => 6 DCFZ\n"
          "44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL\n"
          "12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"
          "179 ORE => 7 PSHF\n"
          "177 ORE => 5 HKGWZ\n"
          "7 DCFZ, 7 PSHF => 2 XJWVT\n"
          "165 ORE => 2 GPVTF\n"
          "3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT\n", 13312 },

        { "2 VPVL, 7 FWMGM, 2 CXFTF, 11 MNCFX => 1 STKFG\n"
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
          "176 ORE => 6 VJHF\n", 180697 },

        { "171 ORE => 8 CNZTR\n"
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
          "5 BHXH, 4 VRPVC => 5 LTCX\n", 2210736 },

        { "165 ORE => 2 PNBGW\n"
          "2 FTZDF, 14 RHWGQ => 8 JTRM\n"
          "1 QSKQ, 1 GPRK => 8 HKXF\n"
          "2 GKLGP => 3 MTJLK\n"
          "4 HXMPQ => 8 VCRLF\n"
          "2 DMXC, 2 MTJLK => 8 QSKQ\n"
          "39 TCLZ, 17 DKHX, 7 HVPQT, 1 DWMW, 33 THWX, 67 JVGP, 44 RDZSG, 7 JCKT, 22 TDSC, 1 QHVR => 1 FUEL\n"
          "6 VCRLF, 1 HXMPQ, 6 WQSDR => 3 GKLGP\n"
          "1 WLSQZ => 1 WQSDR\n"
          "1 MTJLK => 2 PVSV\n"
          "5 HVPQT, 4 WCTW => 8 NWGDN\n"
          "3 KNTQG => 9 TCLZ\n"
          "1 JTRM, 3 QSKQ, 2 RGWB => 9 RDZSG\n"
          "1 MTJLK, 15 DZMQ => 6 RCPN\n"
          "1 PVSV, 3 HBWDW => 7 DZMQ\n"
          "1 CTKPZ, 2 HKXF => 3 RFCDH\n"
          "5 QNXTS, 2 GSJNV, 1 JVGP, 10 HJTHM, 5 HKXF, 10 DZMQ => 4 JCKT\n"
          "1 PNBGW => 2 HVPQT\n"
          "187 ORE => 1 XLNC\n"
          "16 GPRK => 6 QNXTS\n"
          "1 FTZDF => 9 GPRK\n"
          "9 KNTQG => 2 WCTW\n"
          "35 WQSDR, 2 HVPQT => 8 RPVGN\n"
          "5 RPVGN => 2 RHWGQ\n"
          "1 CTKPZ, 9 QSKQ, 2 QNXTS => 5 DTFRT\n"
          "1 HXMPQ, 12 VCRLF, 1 RHQH => 6 FTZDF\n"
          "3 RHWGQ, 19 DZMQ, 8 FPNMC => 9 FGNK\n"
          "7 RHQH, 3 HWSG => 9 HBWDW\n"
          "11 QNXTS, 1 CNVKX => 8 QHVR\n"
          "4 HVPQT => 6 NRLP\n"
          "4 NWGDN, 1 HWSG => 2 DMXC\n"
          "20 DTFRT, 4 NRLP, 1 CTKPZ => 8 HJTHM\n"
          "2 BSVPD, 7 RHQH => 6 FPNMC\n"
          "3 NSRB => 4 BSVPD\n"
          "1 DZMQ => 3 GSJNV\n"
          "2 GMNXP, 4 GSJNV, 1 ZRBR => 3 WPWM\n"
          "6 RCPN => 4 CNVKX\n"
          "1 NSRB => 5 RGWB\n"
          "22 VCRLF => 4 NSRB\n"
          "4 XLNC, 24 KNTQG => 9 WLSQZ\n"
          "36 NWGDN => 2 WQZQ\n"
          "5 CPMCX, 2 FGNK, 5 DTFRT => 2 ZRBR\n"
          "1 CTKPZ, 1 GMNXP, 6 QNXTS => 4 KRDWH\n"
          "9 RHWGQ, 16 FTZDF, 1 JVGP, 1 GMNXP, 3 HKXF, 9 DTFRT, 27 CTKPZ, 1 GKLGP => 9 DWMW\n"
          "5 WQSDR, 4 NRLP, 3 TCLZ => 1 RHQH\n"
          "4 NRLP => 5 GMNXP\n"
          "158 ORE => 5 KNTQG\n"
          "24 GMNXP, 6 JVGP, 1 BHVR, 4 KRDWH, 1 WPWM, 2 RFCDH => 7 TDSC\n"
          "1 WCTW => 7 HXMPQ\n"
          "10 BSVPD => 9 THWX\n"
          "18 RGWB, 1 HJTHM => 3 DKHX\n"
          "1 WQZQ, 4 VCRLF, 10 HVPQT => 3 CPMCX\n"
          "14 BSVPD, 6 FPNMC, 5 TCLZ => 8 JVGP\n"
          "4 WQZQ, 1 HXMPQ, 4 VCRLF => 3 HWSG\n"
          "2 HWSG => 9 CTKPZ\n"
          "4 NSRB, 1 GPRK => 4 BHVR\n", 337075 }
    };

    for ( auto&& datum : data )
    {
        std::stringstream ss(datum.first);
        nanofactory nf(ss);
        auto result = nf.calc_ore_for(1, "FUEL");
        std::cout << "nf:\n" << nf << "\nexpected: " << datum.second << ", result: " << result << "\n\n";
    }

    return 0;
}
