
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <sudoku/grid.hpp>
#include <sudoku/grid_reader.hpp>
#include <sudoku/solver.hpp>
#include <signal_handler/signal_handler.hpp>

#include <user_input.hpp>

namespace evilquinn
{
namespace sudoku
{

namespace ansi_escapes
{
static const std::string escape = "\33[";
static const char move_up   = 'A';
static const char move_down = 'B';
static const char move_left = 'D';
std::string move_by(char d, int n)
{
    return escape + boost::lexical_cast<std::string>(n) + d;
}
static const std::string clear_current_line    = escape + 'K';
static const std::string clear_cursor_to_end   = escape + "0K";
static const std::string clear_cursor_to_start = escape + "1K";
static const std::string clear_entire_line     = escape + "2K";


} // ansi_escapes


class display
{
public:
    display() :
        lines_(9, ""),
        message_(""),
        prompt_("> "),
        prompt_up_(0)
    {
        std::cout << "\n";
        write_lines();
    }
    void show_prompt()
    {
        std::cout << "\n";
        update_screen();
    }
    void show_grid(grid g)
    {
        std::stringstream lines;
        lines << g;
        lines_.clear();
        std::string line;
        while ( std::getline(lines, line) )
        {
            lines_.emplace_back(std::move(line));
        }
        update_screen();
    }
    void clear_grid()
    {
        for ( auto&& line : lines_ )
        {
            line.clear();
        }
        update_screen();
    }
    std::string get_command()
    {
        std::string command;
        std::getline(std::cin, command);
        prompt_up_ = 1;
        return command;
    }
    void show_message(std::string message)
    {
        message_ = message;
        update_screen();
        message_ = "";
    }
    void refresh()
    {
        update_screen();
    }
private:
    void update_screen()
    {
        std::cout << ansi_escapes::move_by(ansi_escapes::move_up, lines_.size() + 3)
                  << ansi_escapes::move_by(ansi_escapes::move_left, 1000); // bound to get us to start of line, right?
        write_lines();
        prompt_up_ = 0;
    }
    void write_lines()
    {
        for ( auto&& line : lines_ )
        {
            std::cout << ansi_escapes::clear_entire_line << line << "\n";
        }
        std::cout << ansi_escapes::clear_entire_line << message_ << "\n";
        std::cout << ansi_escapes::clear_entire_line << prompt_ << "\n"
                  << ansi_escapes::clear_current_line;
    }
    typedef std::vector<std::string> lines_type;
    lines_type lines_;
    std::string message_;
    std::string prompt_;
    int prompt_up_;
};

class command_handler
{
public:
    explicit command_handler(display& display) :
        display_(display)
    {}
    void operator()(const std::string& message)
    {
        handle_command(message);
    }
    void handle_command(const std::string& command)
    {
        if ( command == "help" ) return display_.show_message("helpful message, right?");
        return display_.show_message("unrecognised command: " + command + ", try \"help\"");
    }
private:
    void show_help()
    {
        display_.show_message("helpful message!");
    }
    display& display_;
};

} // sudoku
} // evilquinn


int main()
{
    boost::asio::io_context asio_context;
    evilquinn::register_signal_handler();
    evilquinn::sudoku::grid_reader reader(
        "/home/evilquinn/git/projeul/sudoku/p096_sudoku_single.txt" );

    evilquinn::sudoku::display ui;
    ui.show_prompt();

    evilquinn::user_input user_input(asio_context);
    user_input.set_observer(evilquinn::sudoku::command_handler(ui));
    auto grid_from_file = reader.getgrid();
    ui.show_grid(*grid_from_file);

    asio_context.run();


    return 0;
}
