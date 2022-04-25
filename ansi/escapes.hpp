#ifndef PROJEUL_ANSI_ESCAPES_ESCAPES_HPP
#define PROJEUL_ANSI_ESCAPES_ESCAPES_HPP

#include <string>
#include <boost/lexical_cast.hpp>

namespace ansi_escapes
{
std::string move_by(char d, int n);
namespace move
{
std::string by(char d, int n);
std::string up(int n);
std::string down(int n);
std::string left(int n);
};
namespace style
{
enum ground_id
{
    foreground = '3',
    background = '4'
};
const char style_modifier = 'm';
namespace fg
{
extern const std::string black;
extern const std::string red;
extern const std::string green;
extern const std::string yellow;
extern const std::string blue;
extern const std::string magenta;
extern const std::string cyan;
extern const std::string white;
};
namespace bg
{
extern const std::string black;
extern const std::string red;
extern const std::string green;
extern const std::string yellow;
extern const std::string blue;
extern const std::string magenta;
extern const std::string cyan;
extern const std::string white;
};

extern const std::string reset;
std::string by_arg(enum ground_id ground, int n);
std::string by_arg_256(enum ground_id ground, int n);
std::string brighten(std::string s);

extern const std::string bold;
extern const std::string underline;
extern const std::string invert;
};

extern const std::string clear_current_line;
extern const std::string clear_cursor_to_end;
extern const std::string clear_cursor_to_start;
extern const std::string clear_entire_line;

//const std::string set_x10_mouse = escape +

#define SET_X10_MOUSE 9
#define SET_VT200_MOUSE 1000
#define SET_VT200_HIGHLIGHT_MOUSE 1001
#define SET_BTN_EVENT_MOUSE 1002
#define SET_ANY_EVENT_MOUSE 1003



} // ansi_escapes

#endif // PROJEUL_ANSI_ESCAPES_ESCAPES_HPP
