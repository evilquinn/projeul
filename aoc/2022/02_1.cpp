
#include <iostream>
#include <fstream>
#include <vector>

#include <aoc/path_def.hpp>

static const char rock = 'A';
static const char paper = 'B';
static const char scissors = 'C';

static const int rock_score = 1;
static const int paper_score = 2;
static const int scissors_score = 3;

static const int lose_score = 0;
static const int draw_score = 3;
static const int win_score = 6;


int rhs_play_score(const std::string& game)
{
    if ( game.size() != 3 ) throw std::runtime_error("Invalid game string");
    switch (game[2])
    {
    case rock     : return rock_score;
    case paper    : return paper_score;
    case scissors : return scissors_score;
    default : throw std::runtime_error("Unrecognised play");
    }
}

int result_score(const std::string game)
{
    if ( game.size() != 3 ) throw std::runtime_error("Invalid game string");
    char lhs = game[0];
    char rhs = game[2];
    if ( lhs == rhs ) return draw_score;
    if ( lhs-1 == rhs ) return lose_score;
    if ( lhs == rhs-1 || rhs == rock ) return win_score;
    return lose_score;
}

void test_result_score()
{
    using test_data_type = std::vector<std::pair<std::string, int> >;
    test_data_type test_data = {
        { "A C", lose_score },
        { "B A", lose_score },
        { "C B", lose_score },
        { "A A", draw_score },
        { "B B", draw_score },
        { "C C", draw_score },
        { "A B", win_score },
        { "B C", win_score },
        { "C A", win_score }
    };
    for ( auto&& datum : test_data )
    {
        if ( result_score(datum.first) != datum.second ) throw std::runtime_error("Test case failed");
    }
}

int game_score(const std::string& game)
{
    return result_score(game) + rhs_play_score(game);
}

int count_scores(std::istream& input)
{
    int result = 0;
    std::string game_line;
    while(std::getline(input, game_line))
    {
        if ( game_line == "" ) continue;
        if ( game_line.size() != 3 ) throw std::runtime_error("Invalid game string");
        if ( game_line[2] > scissors ) game_line[2] -= 23; // normalise X, Y, Z to A, B, C
        result += game_score(game_line);
    }
    return result;
}


int main()
{
    test_result_score();

    std::ifstream input(PROJEUL_AOC_PATH "/02_input.txt");
    if ( !input ) throw std::runtime_error("Failed to open input file");

    int result = count_scores(input);
    std::cout << "Part 1 result: " << result << std::endl;




    return 0;
}
