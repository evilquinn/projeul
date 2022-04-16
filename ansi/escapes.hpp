#include <string>
#include <boost/lexical_cast.hpp>

namespace ansi_escapes
{
static const std::string escape = "\033[";
static const char direction_up   = 'A';
static const char direction_down = 'B';
static const char direction_left = 'D';
std::string move_by(char d, int n)
{
    return escape + boost::lexical_cast<std::string>(n) + d;
}
class move
{
public:
static std::string by(char d, int n) { return escape + boost::lexical_cast<std::string>(n) + d; }
static std::string up(int n) { return move::by(direction_up, n); }
static std::string down(int n) { return move::by(direction_down, n); }
static std::string left(int n) { return move::by(direction_left, n); }
};
static const std::string clear_current_line    = escape + 'K';
static const std::string clear_cursor_to_end   = escape + "0K";
static const std::string clear_cursor_to_start = escape + "1K";
static const std::string clear_entire_line     = escape + "2K";

//static const std::string set_x10_mouse = escape +

#define SET_X10_MOUSE 9
#define SET_VT200_MOUSE 1000
#define SET_VT200_HIGHLIGHT_MOUSE 1001
#define SET_BTN_EVENT_MOUSE 1002
#define SET_ANY_EVENT_MOUSE 1003



} // ansi_escapes
