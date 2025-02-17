#ifndef PROJEUL_ANSI_ESCAPES_ESCAPES_HPP
#define PROJEUL_ANSI_ESCAPES_ESCAPES_HPP

#include <format>
#include <string>

namespace ansi_escapes
{
static const std::string escape = "\033[";
// deprecated, use move::by instead
inline std::string move_by(char direction, int n) { return std::format("{}{}{}", escape, n, direction); }
namespace move
{
namespace dir
{
static const char up    = 'A';
static const char down  = 'B';
static const char right = 'C';
static const char left  = 'D';
}  // namespace dir
inline std::string by(char direction, int n) { return std::format("{}{}{}", escape, n, direction); }
inline std::string up(int n) { return by(dir::up, n); }
inline std::string down(int n) { return by(dir::down, n); }
inline std::string right(int n) { return by(dir::right, n); }
inline std::string left(int n) { return by(dir::left, n); }
};  // namespace move
namespace style
{
static const char foreground     = '3';
static const char background     = '4';
static const char style_modifier = 'm';
namespace fg
{
static const std::string black   = std::format("{}{}{}{}", escape, foreground, '0', style_modifier);
static const std::string red     = std::format("{}{}{}{}", escape, foreground, '1', style_modifier);
static const std::string green   = std::format("{}{}{}{}", escape, foreground, '2', style_modifier);
static const std::string yellow  = std::format("{}{}{}{}", escape, foreground, '3', style_modifier);
static const std::string blue    = std::format("{}{}{}{}", escape, foreground, '4', style_modifier);
static const std::string magenta = std::format("{}{}{}{}", escape, foreground, '5', style_modifier);
static const std::string cyan    = std::format("{}{}{}{}", escape, foreground, '6', style_modifier);
static const std::string white   = std::format("{}{}{}{}", escape, foreground, '7', style_modifier);
};  // namespace fg
namespace bg
{
static const std::string black   = std::format("{}{}{}{}", escape, background, '0', style_modifier);
static const std::string red     = std::format("{}{}{}{}", escape, background, '1', style_modifier);
static const std::string green   = std::format("{}{}{}{}", escape, background, '2', style_modifier);
static const std::string yellow  = std::format("{}{}{}{}", escape, background, '3', style_modifier);
static const std::string blue    = std::format("{}{}{}{}", escape, background, '4', style_modifier);
static const std::string magenta = std::format("{}{}{}{}", escape, background, '5', style_modifier);
static const std::string cyan    = std::format("{}{}{}{}", escape, background, '6', style_modifier);
static const std::string white   = std::format("{}{}{}{}", escape, background, '7', style_modifier);
};  // namespace bg

static const std::string reset = std::format("{}{}{}", escape, '0', style_modifier);
static const std::string brighten_modifier = ";1";
inline std::string by_arg(char ground, int n) { return std::format("{}{}{}{}", escape, ground, n, style_modifier); }
inline std::string by_arg_256(char ground, int n) { return std::format("{}{}{}{}{}", escape, ground, "8;5;", n, style_modifier); }
inline std::string brighten(std::string s) { s.insert(s.find_last_of(style_modifier), brighten_modifier); return s; }

static const std::string bold      = std::format("{}{}{}", escape, '1', style_modifier);
static const std::string underline = std::format("{}{}{}", escape, '4', style_modifier);
static const std::string invert    = std::format("{}{}{}", escape, '7', style_modifier);
};  // namespace style

static const std::string clear_current_line    = std::format("{}{}", escape, 'K');
static const std::string clear_cursor_to_end   = std::format("{}{}", escape, "0K");
static const std::string clear_cursor_to_start = std::format("{}{}", escape, "1K");
static const std::string clear_entire_line     = std::format("{}{}", escape, "2K");

// const std::string set_x10_mouse = escape +

#define SET_X10_MOUSE 9
#define SET_VT200_MOUSE 1000
#define SET_VT200_HIGHLIGHT_MOUSE 1001
#define SET_BTN_EVENT_MOUSE 1002
#define SET_ANY_EVENT_MOUSE 1003

}  // namespace ansi_escapes

#endif  // PROJEUL_ANSI_ESCAPES_ESCAPES_HPP
