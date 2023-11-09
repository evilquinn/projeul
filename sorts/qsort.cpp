
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <iomanip>
#include <cmath>
#include <boost/lexical_cast.hpp>

bool init_display(int lines)
{
    for ( int i = 0; i < lines; ++i )
    {
        std::cout << '\n';
    }
    return true;
}

void display(std::vector<int> const& list, int red = -1, int blue = -1)
{
    const auto max_value_iter = std::max_element(list.begin(), list.end());
    int max_value = *max_value_iter < 0 ? 0 : *max_value_iter;
    const auto min_value_iter = std::max_element(list.begin(), list.end(), std::greater<int>());
    int min_value = *min_value_iter > 0 ? 0 : *min_value_iter;

    int display_height = max_value - min_value;
    static bool screen_init = init_display(display_height); (void)screen_init; // and discard result
    std::cout << std::string("\033[") + boost::lexical_cast<std::string>(display_height) + 'A'; // move cursor to start of display again

    for(int row_ctr = max_value; row_ctr >= min_value; --row_ctr)
    {
        if ( row_ctr == 0 ) continue;
        std::cout << "\033[37m" << std::setw(2) << row_ctr << ": ";
        for ( size_t col = 0; col < list.size(); ++col )
        {
            std::string colour = std::string("\033[37m"); // white
            if ( (size_t)red == col ) colour = std::string("\033[31m"); // red
            if ( (size_t)blue == col ) colour = std::string("\033[34m"); // blue
            std::cout << colour;
            if ( list[col] > 0 && row_ctr > 0 && list[col] >= row_ctr )
            {
                std::cout << '#';
            }
            else if ( list[col] < 0 && row_ctr < 0 && list[col] <= row_ctr )
            {
                std::cout << '#';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

size_t qpart(std::vector<int>& list, size_t start, size_t limit, std::function<bool(const int&)> pred)
{
    if ( limit <= start ) throw std::runtime_error("bad partition arguments");
    while (pred(list[start])) ++start;
    if ( start == limit ) return start;
    for ( size_t i = start + 1; i < limit; ++i )
    {
        if ( pred(list[i]) )
        {
            display(list, i, start);
            std::swap(list[start], list[i]);
            display(list, start, i);
            ++start;
        }
    }
    return start;
}
void qsort(std::vector<int>& list, size_t start, size_t limit)
{
    if ( limit <= start ) return;
    if ( list.size() < limit ) throw std::runtime_error("indexes don't fit in list!");
    int v = list[limit-1];
    //auto pivot = std::partition(list.begin() + start, list.begin() + limit, [&](const int& i) { return i < v; });
    //qsort(list, start, std::distance(list.begin(), pivot));
    //pivot = std::partition(pivot, list.begin() + limit, [&](const int& i){ return i == v; });
    //qsort(list, std::distance(list.begin(), pivot), limit);
    auto pivot = qpart(list, start, limit, [&](const int& i) { return i < v; });
    qsort(list, start, pivot);
    pivot = qpart(list, pivot, limit, [&](const int& i){ return i == v; });
    qsort(list, pivot, limit);
}

void print(std::ostream& os, std::vector<int> const& list)
{
    std::string sep;
    for( size_t i = 0; i < list.size(); ++i )
    {
        os << sep << list[i];
        sep = ", ";
    }
}
std::ostream& operator<< (std::ostream& os, std::vector<int> const& list)
{
    print(os, list);
    return os;
}

int main()
{
    std::vector<int> list = { 7, 4, 2, 8, 5, 0, -3, 7, 8, -1, 5, 2, 8, 4, 5, -8, -9, 1, 5, 3, 1 };

    std::cout << list << std::endl;
    qsort(list, 0, list.size());
    //std::cout << list << std::endl;
    display(list);
    return 0;
}
