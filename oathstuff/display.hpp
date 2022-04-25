#ifndef PROJEUL_OATHSTUFF_DISPLAY_HPP
#define PROJEUL_OATHSTUFF_DISPLAY_HPP

#include <string>
#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>

#include "key_data.hpp"

class rotating_string
{
public:
    rotating_string();
    rotating_string(std::string s, size_t width);
    std::string get();
private:
    static const size_t num_dots = 2;
    std::string s_;
    size_t width_;
    size_t i_;
};

class totps_display
{
public:
    totps_display(boost::asio::io_context& asio_context, keys_data_type keys);
private:
    void update();
    void generate_totps();

    boost::asio::io_context& asio_context_;
    boost::asio::deadline_timer timer_;

    struct state
    {
        std::string totp;
        rotating_string display_name;
        key_data key_info;
        size_t seconds_to_update;
    };
    std::vector<state> states_;
};

#endif // PROJEUL_OATHSTUFF_DISPLAY_HPP
