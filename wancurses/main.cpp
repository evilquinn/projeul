#include <utility>
#include <map>
#include <boost/asio.hpp>
#include <boost/asio/posix/descriptor.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include <ncurses/curses.h>

class input_observer
{
public:
    virtual ~input_observer(){};
    virtual bool on_input() = 0;
};

class input_listener
{
public:
    input_listener(boost::asio::io_context& io_context,
                   const boost::shared_ptr<input_observer>& observer) :
        io_context_(io_context),
        input_stream_(io_context_, 0),
        observer_(observer)
    {
        if ( !observer_ ) throw std::runtime_error("observer_ is NULL");
        wait_for_input();
    };
    void on_input(const boost::system::error_code& ec)
    {
        if ( ec ) return;
        if ( observer_->on_input() ) wait_for_input();
    }
    void wait_for_input()
    {
        input_stream_.async_wait(boost::asio::posix::descriptor::wait_type::wait_read,
                                 boost::bind(&input_listener::on_input,
                                             this,
                                             boost::placeholders::_1));
    }

private:
    boost::asio::io_context& io_context_;
    boost::asio::posix::stream_descriptor input_stream_;
    boost::shared_ptr<input_observer> observer_;
};

class processor : public input_observer
{
public:
    processor(boost::asio::io_context& io_context) :
        io_context_(io_context),
        refresh_timer_(io_context_)
    {
        init_windows();
    }
    ~processor()
    {
        printf("\033[?1003l\n");
        for ( auto&& window : windows_ ) delwin(window);
    }
    bool on_input()
    {
        for ( auto ch = wgetch(stdscr); ch != ERR; ch = wgetch(stdscr) )
        {
            switch(ch)
            {
            case KEY_MOUSE:
            {
                MEVENT event;
                if (getmouse(&event) == OK)
                {
                    handle_mouse(event);
                }
                break;
            }
            case 'q':
            {
                return false;
            }
            default:
            {
                mvwprintw(status_bar_, 0, 0, "Key: %d ('%c')\n", ch, ch);
                break;
            }
            }
        }
        return true;
    }
private:
    void init_windows();
    void refresh_windows()
    {
        static boost::function<void(const boost::system::error_code&)> refresh_loop =
        [&](const boost::system::error_code& ec)
        {
            if (!ec)
            {
                for ( auto&& window : windows_ ) wnoutrefresh(window);
                doupdate();

                refresh_timer_.expires_from_now(boost::posix_time::milliseconds(20));
                refresh_timer_.async_wait(boost::bind(refresh_loop, boost::placeholders::_1));
            }
        };
        io_context_.post(boost::bind(refresh_loop, boost::system::error_code()));
    }
    void handle_mouse(const MEVENT& event)
    {
        std::string mouse_state_str;

        if ( BUTTON_CTRL           & event.bstate ) mouse_state_str += "Ctrl;";
        if ( BUTTON_SHIFT          & event.bstate ) mouse_state_str += "Shift;";
        if ( BUTTON_ALT            & event.bstate ) mouse_state_str += "Alt;";
        if ( REPORT_MOUSE_POSITION & event.bstate ) mouse_state_str += "Report mouse position;";

        if ( BUTTON_RELEASE(event.bstate,        1) ) mouse_state_str += "Mouse 1 release;";
        if ( BUTTON_PRESS(event.bstate,          1) ) mouse_state_str += "Mouse 1 press;";
        if ( BUTTON_CLICK(event.bstate,          1) ) mouse_state_str += "Mouse 1 click;";
        if ( BUTTON_DOUBLE_CLICK(event.bstate,   1) ) mouse_state_str += "Mouse 1 dboule-click;";
        if ( BUTTON_TRIPLE_CLICK(event.bstate,   1) ) mouse_state_str += "Mouse 1 triple-click;";

        if ( BUTTON_RELEASE(event.bstate,        2) ) mouse_state_str += "Mouse 2 release;";
        if ( BUTTON_PRESS(event.bstate,          2) ) mouse_state_str += "Mouse 2 press;";
        if ( BUTTON_CLICK(event.bstate,          2) ) mouse_state_str += "Mouse 2 click;";
        if ( BUTTON_DOUBLE_CLICK(event.bstate,   2) ) mouse_state_str += "Mouse 2 dboule-click;";
        if ( BUTTON_TRIPLE_CLICK(event.bstate,   2) ) mouse_state_str += "Mouse 2 triple-click;";

        if ( BUTTON_RELEASE(event.bstate,        3) ) mouse_state_str += "Mouse 3 release;";
        if ( BUTTON_PRESS(event.bstate,          3) ) mouse_state_str += "Mouse 3 press;";
        if ( BUTTON_CLICK(event.bstate,          3) ) mouse_state_str += "Mouse 3 click;";
        if ( BUTTON_DOUBLE_CLICK(event.bstate,   3) ) mouse_state_str += "Mouse 3 dboule-click;";
        if ( BUTTON_TRIPLE_CLICK(event.bstate,   3) ) mouse_state_str += "Mouse 3 triple-click;";

        if ( BUTTON_RELEASE(event.bstate,        4) ) mouse_state_str += "Mouse 4 release;";
        if ( BUTTON_PRESS(event.bstate,          4) ) mouse_state_str += "Scroll down;";
        if ( BUTTON_CLICK(event.bstate,          4) ) mouse_state_str += "Mouse 4 click;";
        if ( BUTTON_DOUBLE_CLICK(event.bstate,   4) ) mouse_state_str += "Mouse 4 dboule-click;";
        if ( BUTTON_TRIPLE_CLICK(event.bstate,   4) ) mouse_state_str += "Mouse 4 triple-click;";

        if ( BUTTON_RELEASE(event.bstate,        5) ) mouse_state_str += "Mouse 5 release;";
        if ( BUTTON_PRESS(event.bstate,          5) ) mouse_state_str += "Scroll up;";
        if ( BUTTON_CLICK(event.bstate,          5) ) mouse_state_str += "Mouse 5 click;";
        if ( BUTTON_DOUBLE_CLICK(event.bstate,   5) ) mouse_state_str += "Mouse 5 dboule-click;";
        if ( BUTTON_TRIPLE_CLICK(event.bstate,   5) ) mouse_state_str += "Mouse 5 triple-click;";

        mvwprintw(status_bar_, 0, 0, "Mouse: id=%d, x=%d, y=%d, z=%d, bstate=0x%08x, desc=%s\n",
                  event.id, event.y, event.x, event.z, event.bstate, mouse_state_str.c_str());
        prepend_to_tail(event.y, event.x);
    }
    void prepend_to_tail(int y, int x)
    {
        static boost::function<void(const boost::system::error_code&, int, int, int)> decay_loop =
        [&](const boost::system::error_code& ec, int y, int x, int c)
        {
            if (!ec)
            {
                mvwaddch(canvas_, y, x, ' ' | COLOR_PAIR(tail_colour_b_[--c]));
                auto t = decay_timers_.find({y, x});
                if ( c )
                {
                    if ( t == decay_timers_.end() ) throw std::runtime_error("timer wasn't there...");
                    t->second.expires_from_now(boost::posix_time::seconds(1));
                    t->second.async_wait(boost::bind(decay_loop, boost::placeholders::_1, y, x, c));
                }
                else
                {
                    decay_timers_.erase(t);
                }
            }
        };
        decay_timers_.emplace(std::make_pair(std::make_pair(y, x), boost::asio::deadline_timer(io_context_)));
        io_context_.post(boost::bind(decay_loop, boost::system::error_code(), y, x, num_tail_colours_));
    }
    boost::asio::io_context& io_context_;
    WINDOW* status_bar_;
    WINDOW* canvas_;
    WINDOW* windows_[2];
    static const int num_tail_colours_;
    static const short tail_colour_b_[];
    std::map<std::pair<int, int>, boost::asio::deadline_timer> decay_timers_;
    boost::asio::deadline_timer refresh_timer_;
};

const short processor::tail_colour_b_[] = { COLOR_BLACK, COLOR_WHITE, COLOR_YELLOW, COLOR_GREEN, COLOR_BLUE, COLOR_MAGENTA, COLOR_RED };
const int processor::num_tail_colours_ = sizeof(processor::tail_colour_b_) / sizeof(processor::tail_colour_b_[0]);

void processor::init_windows()
{
    start_color();
    windows_[0] = canvas_ = newwin(LINES - 1, COLS, 0, 0); // every line but for one at the bottom
    windows_[1] = status_bar_ = newwin(1, COLS, LINES - 1, 0); // one line, at the bottom
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1003h\n");
    refresh_windows();
    // colours
    for ( auto&& colour_id : tail_colour_b_ )
    {
        init_pair(colour_id, colour_id, colour_id);
    }
}

int main()
{
    initscr();
    scrollok(stdscr, true);
    refresh();

    boost::asio::io_context io_context;
    boost::shared_ptr<processor> io_processor = boost::make_shared<processor>(io_context);
    boost::shared_ptr<input_listener> io_listener = boost::make_shared<input_listener>(io_context, io_processor);

    io_context.run();

    endwin();
    return 0;
}
