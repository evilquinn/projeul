
#include <iostream>
#include <random>
#include <cstring>

#include <ncurses/ncurses.h>

/**
 * copied/ported from https://gist.github.com/msimpson/1096950
 */

namespace
{
std::random_device rdev;
std::mt19937 rgen(rdev());
std::uniform_real_distribution<> rdist;
}

int main()
{
    initscr();
    start_color();
    auto width = getmaxx(stdscr);
    auto height = getmaxy(stdscr);
    auto size = width * height;
    char c[] = { ' ', '.', ':', '^', '*', 'x', 's', 'S', '#', '$' };
    const int buffer_size = size + width + 1;
    int b[buffer_size];
    memset(b, 0, buffer_size);

    init_pair(1, 0, 0);
    init_pair(2, 1, 0);
    init_pair(3, 3, 0);
    init_pair(4, 4, 0);
    clear();

    while(true)
    {
        for ( int i = 0; i < width/9; ++i )
        {
            b[int((rdist(rgen)*width)+width*(height-1))] = 65;
        }
        for ( int i = 0; i < size; ++i )
        {
            b[i] = (b[i]+b[i+1]+b[i+width]+b[i+width+1])/4;
            auto colour = b[i] > 15 ? 4 :
                          b[i] >  9 ? 3 :
                          b[i] >  4 ? 2 :
                                      1 ;
            if ( i < size - 1 )
            {
                mvaddch(i/width, i%width, c[b[i]>9?9:b[i]] | COLOR_PAIR(colour) | A_BOLD );
            }
        }
        refresh();
        timeout(30);
        if ( getch() != -1 ) break;
    }

    endwin();
    return 0;
}
