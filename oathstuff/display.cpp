
#include "display.hpp"


#include <iostream>
#include <ctime>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <liboath/oath.h>
#include <ansi/escapes.hpp>

rotating_string::rotating_string()
{}
rotating_string::rotating_string(std::string s, size_t width) :
    s_(s),
    width_(width),
    i_(0)
{}
std::string rotating_string::get()
{
    size_t to_display = s_.size() - i_;
    if ( to_display <= width_ )
    {
        auto result = s_.substr(i_, to_display);
        i_ = 0;
        result.append(width_ - to_display, ' ');
        return result;
    }
    size_t can_display = width_ - num_dots;
    std::string result(s_.data() + i_, can_display);
    result.append("..");
    ++i_;
    return result;
}
static const size_t num_dots = 2;
totps_display::totps_display(boost::asio::io_context& asio_context, keys_data_type keys) :
    asio_context_(asio_context),
    timer_(asio_context)
{
    states_.resize(keys.size());
    for ( size_t i = 0; i < keys.size(); ++i )
    {
        std::cout << "\n"; // prepare screen real estate
        states_[i].display_name = rotating_string(keys[i].id, 20);
        states_[i].key_info = keys[i];
    }
    if ( states_.size() == 0 ) std::cout << "\n"; // For the single "No keys..." line
    asio_context_.post(boost::bind(&totps_display::update, this));
}
void totps_display::update()
{
    generate_totps();
    std::cout << ansi_escapes::move::left(1000) << ansi_escapes::move::up(states_.size());
    for ( size_t i = 0; i < states_.size(); ++i )
    {
        std::cout << "| " << states_[i].display_name.get()
                  << " | " << std::setw(8) << states_[i].totp
                  << " | " << std::setw(3) << states_[i].seconds_to_update << "s"
                  << " |" << std::endl;
    }
    if ( states_.size() == 0 )
    {
        std::cout << "No keys..." << std::endl;
    }
    timer_.expires_from_now(boost::posix_time::seconds(1));
    timer_.async_wait(boost::bind(&totps_display::update, this));
}
void totps_display::generate_totps()
{
    for ( size_t i = 0; i < states_.size(); ++i )
    {
        states_[i].totp.resize(states_[i].key_info.digits + 1);
        time_t time_now = std::time(NULL);
        states_[i].seconds_to_update =
            states_[i].key_info.interval -
                ( (time_now - states_[i].key_info.offset) % states_[i].key_info.interval );
        int gen_result = oath_totp_generate(reinterpret_cast<char*>(states_[i].key_info.key.data()),
                                            states_[i].key_info.key.size(),
                                            time_now,
                                            states_[i].key_info.interval,
                                            states_[i].key_info.offset,
                                            states_[i].key_info.digits,
                                            &states_[i].totp[0]);
        if ( gen_result != OATH_OK ) throw gen_result;
    }
}
