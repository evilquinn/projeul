
#include <iostream>
#include <map>
#include <iomanip>
#include "escapes.hpp"

int main()
{
    std::cout << "hello" << std::endl;

    std::cout << "Basic 8 colours:" << std::endl;
    for ( int i = 0; i < 8; ++i )
    {
        std::cout << ansi_escapes::style::by_arg(ansi_escapes::style::foreground, i) << std::setw(4) << i;
    }
    std::cout << std::endl;
    std::cout << "Bright colours:" << std::endl;
    for ( int i = 0; i < 8; ++i )
    {
        std::cout << ansi_escapes::style::brighten(ansi_escapes::style::by_arg(ansi_escapes::style::foreground, i)) << std::setw(4) << i;
    }
    std::cout << std::endl;
    std::cout << ansi_escapes::style::reset << std::endl;

    std::cout << "Basic Backgrounds:" << std::endl;
    for ( int i = 0; i < 8; ++i )
    {
        std::cout << ansi_escapes::style::by_arg(ansi_escapes::style::background, i);
        for ( int j = 0; j < 8; ++j )
        {
            std::cout << ansi_escapes::style::by_arg(ansi_escapes::style::foreground, j) << std::setw(4) << i;
        }
        std::cout << ansi_escapes::style::reset << std::endl;
        std::cout << ansi_escapes::style::by_arg(ansi_escapes::style::background, i);
        for ( int j = 0; j < 8; ++j )
        {
            std::cout << ansi_escapes::style::brighten(ansi_escapes::style::by_arg(ansi_escapes::style::foreground, j)) << std::setw(4) << i;
        }
        std::cout << ansi_escapes::style::reset << std::endl;

        std::cout << ansi_escapes::style::brighten(ansi_escapes::style::by_arg(ansi_escapes::style::background, i));
        for ( int j = 0; j < 8; ++j )
        {
            std::cout << ansi_escapes::style::by_arg(ansi_escapes::style::foreground, j) << std::setw(4) << i;
        }
        std::cout << ansi_escapes::style::reset << std::endl;
    }
    std::cout << ansi_escapes::style::reset << std::endl;

    std::cout << "256 colours:" << std::endl;
    int split_at = 7;
    int split_count = 0;
    for ( int i = 0; i < 16; ++i )
    {
        for ( int j = 0; j < 16; ++j )
        {
            int v = i * 16 + j;
            std::cout << ansi_escapes::style::by_arg_256(ansi_escapes::style::foreground, v) << std::setw(4) << v;
            if ( split_count == split_at )
            {
                std::cout << ansi_escapes::style::reset << std::endl;
                split_count = 0;
                if ( v == 15 ) split_at = 5;
            }
            else
            {
                ++split_count;
            }
        }
    }
    std::cout << ansi_escapes::style::reset << std::endl;
    std::cout << std::endl;
    split_at = 7;
    split_count = 0;
    for ( int i = 0; i < 16; ++i )
    {
        for ( int j = 0; j < 16; ++j )
        {
            int v = i * 16 + j;
            std::cout << ansi_escapes::style::by_arg_256(ansi_escapes::style::background, v) << std::setw(4) << v;
            if ( split_count == split_at )
            {
                std::cout << ansi_escapes::style::reset << std::endl;
                split_count = 0;
                if ( v == 15 ) split_at = 5;
            }
            else
            {
                ++split_count;
            }
        }
    }
    std::cout << ansi_escapes::style::reset << std::endl;
    std::cout << std::endl;
    std::cout << ansi_escapes::style::reset << std::endl;

    std::cout << "Styles:" << std::endl;
    enum class style_id { bold, underline, invert };
    std::map<style_id, std::pair<std::string, std::string> > styles =
    {
        { style_id::bold, { "bold", ansi_escapes::style::bold } },
        { style_id::underline, { "underline", ansi_escapes::style::underline } },
        { style_id::invert, { "invert", ansi_escapes::style::invert } }
    };
    std::cout << ansi_escapes::style::bold
              << "bold"
              << ansi_escapes::style::reset << std::endl;
    std::cout << ansi_escapes::style::underline
              << "underline"
              << ansi_escapes::style::reset << std::endl;
    std::cout << ansi_escapes::style::invert
              << "invert"
              << ansi_escapes::style::reset << std::endl;
    std::cout << ansi_escapes::style::bold
              << ansi_escapes::style::underline
              << "bold, underline"
              << ansi_escapes::style::reset << std::endl;
    std::cout << ansi_escapes::style::bold
              << ansi_escapes::style::invert
              << "bold, invert"
              << ansi_escapes::style::reset << std::endl;
    std::cout << ansi_escapes::style::underline
              << ansi_escapes::style::invert
              << "underline, invert"
              << ansi_escapes::style::reset << std::endl;
    std::cout << ansi_escapes::style::bold
              << ansi_escapes::style::underline
              << ansi_escapes::style::invert
              << "bold, underline, invert"
              << ansi_escapes::style::reset << std::endl;

    return 0;
}
