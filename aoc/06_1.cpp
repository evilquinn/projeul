/**
 * Suppose you have the following map:
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
 *
 * Visually, the above map of orbits looks like this:
 *
 *            G - H       J - K - L
 *           /           /
 *   COM - B - C - D - E - F
 *                  \
 *                   I
 * In this visual representation, when two objects are connected by a line, the one on the right directly
 * orbits the one on the left.
 *
 * Here, we can count the total number of orbits as follows:
 *
 * D directly orbits C and indirectly orbits B and COM, a total of 3 orbits.
 * L directly orbits K and indirectly orbits J, E, D, C, B, and COM, a total of 7 orbits.
 * COM orbits nothing.
 * The total number of direct and indirect orbits in this example is 42.
 *
 * What is the total number of direct and indirect orbits in your map data?
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
"K)L\n";


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


int count_orbits(std::istream& ins)
{
    std::string orbit;
    std::unordered_map<std::string, struct orbitum> orbits;
    struct orbitum* com = nullptr;
    while ( ins >> orbit )
    {
        auto b = orbit.find(')');
        std::string so = orbit.substr(0, b);
        orbitum& orbitee = orbits[so];
        if ( so.compare("COM") == 0 ) com = &orbitee;
        orbitum& orbiter = orbits[orbit.substr(b+1)];
        orbiter.orbitee = &orbitee;
        orbitee.orbiters.push_back(&orbiter);
    }
    return sum_counts(com);
}

int count_orbits(const std::string& s)
{
    std::istringstream ins(s);
    return count_orbits(ins);
}

int main()
{
    std::vector<std::pair<std::string, int> > data =
    {
        { orbit_map, 42 }
    };
    for ( auto&& datum : data )
    {
        auto result = count_orbits(datum.first);
        std::cout << "result: " << result << "\n";
    }

    std::ifstream inf(PROJEUL_AOC_PATH "/06_input.txt");
    std::cout << "super result: " << count_orbits(inf) << "\n";
    return 0;
}
