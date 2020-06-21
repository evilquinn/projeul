/**
 * Now, you just need to figure out how many orbital transfers you (YOU) need to take to get to Santa (SAN).
 *
 * You start at the object YOU are orbiting; your destination is the object SAN is orbiting. An orbital
 * transfer lets you move from any object to an object orbiting or orbited by that object.
 *
 * For example, suppose you have the following map:
 *
 * COM)B
 * B)C
 * C)D
 * D)E
 * E)F
 * B)G
 * G)H
 * D)I
 * E)J
 * J)K
 * K)L
 * K)YOU
 * I)SAN
 *
 * Visually, the above map of orbits looks like this:
 *
 *                           YOU
 *                          /
 *         G - H       J - K - L
 *        /           /
 * COM - B - C - D - E - F
 *                \
 *                 I - SAN
 *
 * In this example, YOU are in orbit around K, and SAN is in orbit around I. To move from K to I,
 * a minimum of 4 orbital transfers are required:
 *
 * K to J
 * J to E
 * E to D
 * D to I
 *
 * Afterward, the map of orbits looks like this:
 *
 *         G - H       J - K - L
 *        /           /
 * COM - B - C - D - E - F
 *                \
 *                 I - SAN
 *                  \
 *                   YOU
 *
 * What is the minimum number of orbital transfers required to move from the object YOU are orbiting
 * to the object SAN is orbiting? (Between the objects they are orbiting - not between YOU and SAN.)
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "path_def.hpp"

const std::string orbit_map =
"COM)B\n"
"B)C\n"
"C)D\n"
"D)E\n"
"E)F\n"
"B)G\n"
"G)H\n"
"D)I\n"
"E)J\n"
"J)K\n"
"K)L\n"
"K)YOU\n"
"I)SAN\n";

struct orbitum
{
    std::string name;
    orbitum* orbitee;
    std::vector<orbitum*> orbiters;
};

struct orbits
{
    std::unordered_map<std::string, struct orbitum> mem_;
    struct orbitum* com_;
    orbits(std::istream& ins) :
        mem_(),
        com_()
    {
        std::string orbit;
        while ( ins >> orbit )
        {
            auto split = orbit.find(')');
            std::string so = orbit.substr(0, split);
            orbitum& orbitee = mem_[so];
            if ( so.compare("COM") == 0 )
            {
                com_ = &orbitee;
                com_->name = "COM";
            }
            std::string name = orbit.substr(split+1);
            orbitum& orbiter = mem_[name];
            orbiter.name = name;
            orbiter.orbitee = &orbitee;
            orbitee.orbiters.push_back(&orbiter);
        }
        if ( com_ == nullptr ) throw std::runtime_error("didn't find com! wtf?");
    }
};

class orbits_walker_euler
{
public:
    orbits_walker_euler(orbitum* orb) :
        curr_(orb),
        nexts_(),
        euler_dists_(),
        level_(0)
    {
        traverse_and_map();
    }
    ~orbits_walker_euler()
    {
        //dump_euler_dists();
    }
    void dump_euler_dists()
    {
        for ( auto&& dist : euler_dists_ )
        {
            std::cout << "{ " << dist.first << ", " << dist.second << "}\n";
        }
    }
    void traverse_and_map()
    {
        euler_dists_.push_back({ curr_->name, level_ });
        while ( advance() != nullptr ) {};
    }

    orbitum* advance(int n = 1)
    {
        for ( ; n > 0 && curr_ != nullptr; --n )
        {
            do
            {
                if ( try_next_child() )
                {
                    break;
                }
            } while ( try_parent() );
        }
        return curr_;
    }
    int dist_between(const std::string& a, const std::string& b)
    {
        std::unordered_set<std::string> ss = { a, b };
        auto ff = std::find_first_of(euler_dists_.begin(), euler_dists_.end(), ss.begin(), ss.end(),
            [&](const decltype(euler_dists_)::value_type& l, const std::string& r)
            {
                return l.first == r;
            });
        ss.erase(ff->first);
        auto fs = std::find_if(std::next(ff), euler_dists_.end(),
            [&](const decltype(euler_dists_)::value_type& l)
            {
                return l.first == *ss.begin();
            });
        auto lca = std::min_element(ff, fs,
            [&](const decltype(euler_dists_)::value_type& l, const decltype(euler_dists_)::value_type& r)
            {
                return l.second < r.second;
            });
        return ff->second + fs->second - ( 2 * ( 1 + lca->second ) );
    }

private:
    bool try_next_child()
    {
        // find out idx for the next child to visit for
        // this node
        int& next_child_idx = nexts_[curr_];
        if ( next_child_idx == 0 )
        {
            // if we got the first child, increment the depth
            ++level_;
        }
        else
        {
            // if we're trying subsequent children, mark coming
            // through the parent
            euler_dists_.push_back({ curr_->name, level_ - 1 });
        }

        // no more children, bail
        if ( next_child_idx >= (int)(curr_->orbiters.size()) ) return false;

        // get next
        curr_ = curr_->orbiters[next_child_idx];

        // and mark it in the path
        euler_dists_.push_back({ curr_->name, level_ });

        // and remember to visit the next child
        ++next_child_idx;
        return true;
    }
    bool try_parent()
    {
        // we're walking back levels
        --level_;
        curr_ = curr_->orbitee;
        return curr_ != nullptr;
    }

    orbitum* curr_;
    std::unordered_map<orbitum*, int> nexts_;
    std::vector<std::pair<std::string, int> > euler_dists_;
    int level_;
};

int distance_between(std::istream& ins, const std::string& a, const std::string& b)
{
    struct orbits orbs(ins);
    orbits_walker_euler eulorb(orbs.com_);
    return eulorb.dist_between(a, b);
}

int distance_between(const std::string& s, const std::string& a, const std::string& b)
{
    std::istringstream ins(s);
    return distance_between(ins, a, b);
}

int main()
{
    std::vector<std::pair<std::string, std::pair<std::pair<std::string, std::string>, int> > > data =
    {
        { orbit_map, { { "YOU", "SAN" }, 42 } }
    };
    for ( auto&& datum : data )
    {
        auto result = distance_between(datum.first, datum.second.first.first, datum.second.first.second);
        std::cout << "result: " << result << "\n";
    }

    std::ifstream inf(PROJEUL_AOC_PATH "/06_input.txt");
    std::cout << "super result: " << distance_between(inf, "YOU", "SAN") << "\n";
    return 0;
}
