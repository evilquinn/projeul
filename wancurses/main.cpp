
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <ncurses/curses.h>

class input_handler
{
public:
    input_handler(boost::asio::io_context& io_context) :
        io_context_(io_context),
        timer_(io_context_),
        observer_(boost::bind(&input_handler::echo, this, boost::placeholders::_1))
    {
        ui_window_ = newwin(3, COLS, LINES - 3, 0);
        wresize(stdscr, LINES - 3, COLS);
        waddstr(ui_window_, "Enter command:");
        wmove(ui_window_, 1, 0);
        wrefresh(ui_window_);
        //cbreak();
        //keypad(ui_window_, true);
        //nodelay(ui_window_, true);
        //noecho();
        wait_for_input();
        extra_thread_ = boost::thread(boost::bind(&input_handler::add_thread, this));
    }
    ~input_handler()
    {
        //wborder(ui_window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        wrefresh(ui_window_);
        delwin(ui_window_);
    }
private:
    void add_thread()
    {
        io_context_.run();
    }
    void wait_for_input()
    {
        wmove(ui_window_, 1, 0);
        wclrtoeol(ui_window_);
        timer_.expires_from_now(boost::posix_time::milliseconds(100));
        timer_.async_wait(boost::bind(&input_handler::check_for_input,
                                      this,
                                      boost::placeholders::_1));
    }
    void check_for_input(const boost::system::error_code& ec)
    {
        if ( !ec )
        {
            std::string message_in(128, '\0');
            int ch = wgetnstr(ui_window_, message_in.data(), message_in.size());
            if ( ch != ERR )
            {
                io_context_.post(boost::bind(observer_, std::move(message_in)));
            }
            wait_for_input();
        }

    }
    void echo(int ch, int)
    {
        wechochar(ui_window_, ch);
    }
    void echo(std::string message)
    {
        waddnstr(stdscr, message.data(), message.size());
        wechochar(stdscr, '\n');
    }
    boost::asio::io_context& io_context_;
    boost::asio::deadline_timer timer_;
    boost::function<void(std::string)> observer_;
    boost::thread extra_thread_;
    WINDOW* ui_window_;
};

int main()
{
    initscr();
    scrollok(stdscr, true);
    refresh();

    boost::asio::io_context io_context;
    input_handler ui(io_context);

    io_context.run();

    endwin();
    exit_curses(0);
}
