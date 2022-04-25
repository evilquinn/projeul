
#include "escapes.hpp"
#include <boost/lexical_cast.hpp>

namespace ansi_escapes
{
const std::string escape = "\033[";
const char direction_up   = 'A';
const char direction_down = 'B';
const char direction_left = 'D';
std::string move_by(char d, int n)
{
    return escape + boost::lexical_cast<std::string>(n) + d;
}
namespace move
{
std::string by(char d, int n) { return escape + boost::lexical_cast<std::string>(n) + d; }
std::string up(int n) { return move::by(direction_up, n); }
std::string down(int n) { return move::by(direction_down, n); }
std::string left(int n) { return move::by(direction_left, n); }
};
namespace style
{
namespace fg
{
const std::string black   = escape + static_cast<char>(foreground) + "0" + style_modifier;
const std::string red     = escape + static_cast<char>(foreground) + "1" + style_modifier;
const std::string green   = escape + static_cast<char>(foreground) + "2" + style_modifier;
const std::string yellow  = escape + static_cast<char>(foreground) + "3" + style_modifier;
const std::string blue    = escape + static_cast<char>(foreground) + "4" + style_modifier;
const std::string magenta = escape + static_cast<char>(foreground) + "5" + style_modifier;
const std::string cyan    = escape + static_cast<char>(foreground) + "6" + style_modifier;
const std::string white   = escape + static_cast<char>(foreground) + "7" + style_modifier;
};
namespace bg
{
const std::string black   = escape + static_cast<char>(background) + "0" + style_modifier;
const std::string red     = escape + static_cast<char>(background) + "1" + style_modifier;
const std::string green   = escape + static_cast<char>(background) + "2" + style_modifier;
const std::string yellow  = escape + static_cast<char>(background) + "3" + style_modifier;
const std::string blue    = escape + static_cast<char>(background) + "4" + style_modifier;
const std::string magenta = escape + static_cast<char>(background) + "5" + style_modifier;
const std::string cyan    = escape + static_cast<char>(background) + "6" + style_modifier;
const std::string white   = escape + static_cast<char>(background) + "7" + style_modifier;
};

const std::string reset = escape + '0' + style_modifier;
const std::string brighten_modifier = ";1";
std::string by_arg(enum ground_id ground, int n) { return escape + static_cast<char>(ground) + boost::lexical_cast<std::string>(n) + style_modifier; }
std::string by_arg_256(enum ground_id ground, int n) { return escape + static_cast<char>(ground) + "8;5;" + boost::lexical_cast<std::string>(n) + style_modifier; };
std::string brighten(std::string s) { s.insert(s.find_last_of(style_modifier), brighten_modifier); return s; }

const std::string bold      = escape + '1' + style_modifier;
const std::string underline = escape + '4' + style_modifier;
const std::string invert    = escape + '7' + style_modifier;
};

const std::string clear_current_line    = escape + 'K';
const std::string clear_cursor_to_end   = escape + "0K";
const std::string clear_cursor_to_start = escape + "1K";
const std::string clear_entire_line     = escape + "2K";

} // ansi_escapes
