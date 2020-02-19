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
#include <unordered_map>
#include <map>
#include <boost/algorithm/string.hpp>

#if !defined(PROJEUL_AOC_PATH)
#define PROJEUL_AOC_PATH "."
#endif

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
    int count = 0;
    orbitum* orbitee;
    std::vector<orbitum*> orbiters;
};

int sum_counts(orbitum* o)
{
    int result = 0;
    if ( o->orbitee )
    {
        o->count = o->orbitee->count + 1;
        result += o->count;
    }
    for ( auto&& orbiter : o->orbiters )
    {
        result += sum_counts(orbiter);
    }
    return result;
}

orbitum* common_ancestor(orbitum* a, orbitum* b)
{
    orbitum* result = nullptr;
    return result;
}


int distance_between(std::istream& ins, const std::string& a, const std::string& b)
{
    std::string orbit;
    std::unordered_map<std::string, struct orbitum> orbits;
    struct orbitum* com = nullptr, * noda = nullptr, * nodb = nullptr;
    while ( ins >> orbit )
    {
        auto split = orbit.find(')');
        std::string so = orbit.substr(0, split);
        orbitum& orbitee = orbits[so];
        if ( so.compare("COM") == 0 ) com = &orbitee;
        else if ( so == a ) noda = &orbitee;
        else if ( so == b ) nodb = &orbitee;
        orbitum& orbiter = orbits[orbit.substr(split+1)];
        orbiter.orbitee = &orbitee;
        orbitee.orbiters.push_back(&orbiter);
    }
    return sum_counts(com);
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
