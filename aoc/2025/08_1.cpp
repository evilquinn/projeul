
#include <algorithm>
#include <aoc/path_def.hpp>
#include <cmath>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

/**
 * part 1:
 *
 *
 *
 *
 *
 */

std::string test_string =
    "162,817,812\n"
    "57,618,57\n"
    "906,360,560\n"
    "592,479,940\n"
    "352,342,300\n"
    "466,668,158\n"
    "542,29,236\n"
    "431,825,988\n"
    "739,650,466\n"
    "52,470,668\n"
    "216,146,977\n"
    "819,987,18\n"
    "117,168,530\n"
    "805,96,715\n"
    "346,949,466\n"
    "970,615,88\n"
    "941,993,340\n"
    "862,61,35\n"
    "984,92,344\n"
    "425,690,689\n";

using value_t = int;
template <typename T>
struct basic_coord_t
{
    T x;
    T y;
    T z;
};
using coord_t = basic_coord_t<value_t>;
bool operator<(const coord_t& lhs, const coord_t& rhs)
{
    return lhs.z < rhs.z ? true : lhs.z > rhs.z ? false : lhs.y < rhs.y ? true : lhs.y > rhs.y ? false : lhs.x < rhs.x;
}
bool operator==(const coord_t& lhs, const coord_t& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
double distance_between(const coord_t& p, const coord_t& q)
{
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2) + pow(p.z - q.z, 2));
}
using distances_t = std::map<double, std::pair<coord_t, coord_t>>;

using coords_t = std::vector<coord_t>;

coords_t read_coords(std::istream& is)
{
    coords_t result;
    std::string line;
    while (std::getline(is, line))
    {
        coord_t c;
        std::sscanf(line.c_str(), "%d,%d,%d", &c.x, &c.y, &c.z);
        result.push_back(c);
    }
    return result;
}

distances_t map_distances(const coords_t& coords)
{
    distances_t distances;
    for (size_t i = 0; i < coords.size(); ++i)
    {
        for (size_t j = i + 1; j < coords.size(); ++j)
        {
            distances[distance_between(coords[i], coords[j])] = std::make_pair(coords[i], coords[j]);
        }
    }
    return distances;
}

using circuits_t = std::vector<std::set<coord_t>>;
circuits_t connect_circuits(const coords_t& coords, const distances_t& distances, size_t connections)
{
    circuits_t result;
    for (auto&& coord : coords)
    {
        result.push_back({ coord });
    }
    for (size_t i = 0; i < connections; ++i)
    {
        auto& distance = *std::next(distances.begin(), i);
        auto circuit_it_first =
            std::find_if(result.begin(), result.end(), [&distance](const std::set<coord_t>& circuit) {
                return circuit.find(distance.second.first) != circuit.end();
            });
        auto circuit_it_second =
            std::find_if(result.begin(), result.end(), [&distance](const std::set<coord_t>& circuit) {
                return circuit.find(distance.second.second) != circuit.end();
            });
        if (circuit_it_first == circuit_it_second)
        {
            continue;
        }

        circuit_it_first->insert(circuit_it_second->begin(), circuit_it_second->end());
        result.erase(circuit_it_second);
    }
    return result;
}

size_t largest_product(circuits_t& circuits)
{
    size_t result = 1;
    std::partial_sort(
        circuits.begin(),
        std::next(circuits.begin(), 3),
        circuits.end(),
        [](const std::set<coord_t>& lhs, const std::set<coord_t>& rhs) { return lhs.size() > rhs.size(); });
    for(auto it = circuits.begin(); it != std::next(circuits.begin(), 3); ++it) {
        result *= it->size();
    }
    return result;
}

int main()
{
    std::string input_path(PROJEUL_AOC_PATH "/08_input.txt");
    std::ifstream ifs(input_path);
    if (!ifs)
        throw std::runtime_error(std::string("Error reading input file: ").append(input_path));

    std::istringstream iss(test_string);

    auto coords    = read_coords(ifs);
    auto distances = map_distances(coords);
    auto circuits  = connect_circuits(coords, distances, 1000);
    size_t result  = largest_product(circuits);

    std::cout << "result: " << result << std::endl;

    std::cout << "hello" << std::endl;

    return 0;
}
