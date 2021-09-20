
#include <boost/asio.hpp>
#include <boost/asio/posix/descriptor.hpp>
#include <boost/bind/bind.hpp>
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
    processor()
    {
        status_bar_ = newwin(1, COLS, LINES - 1, 0); // one line, at the bottom
        wrefresh(status_bar_);
        cbreak();
        keypad(stdscr, TRUE);
        nodelay(status_bar_, true);
        noecho();
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
        printf("\033[?1003h\n");
    }
    ~processor()
    {
        printf("\033[?1003l\n");
        delwin(status_bar_);
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
        wrefresh(status_bar_);
        return true;
    }
private:
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

        mvwprintw(status_bar_, 0, 0, "Mouse: id=%d, x=%d, y=%d, z=%d, bstate=0x%08lx, desc=%s\n",
                  event.id, event.y, event.x, event.z, event.bstate, mouse_state_str.c_str());
    }
    WINDOW* status_bar_;
};

int main()
{
    initscr();
    scrollok(stdscr, true);
    refresh();

    boost::asio::io_context io_context;
    boost::shared_ptr<processor> io_processor = boost::make_shared<processor>();
    boost::shared_ptr<input_listener> io_listener = boost::make_shared<input_listener>(io_context, io_processor);

    io_context.run();

    endwin();
}
