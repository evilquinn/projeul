
#include "user_input.hpp"

#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/move/move.hpp>
#include <boost/thread.hpp>

namespace evilquinn
{
user_input::user_input( boost::asio::io_context& io_context ) :
    io_context_(io_context),
    cli_handle_( io_context_, ::dup(STDIN_FILENO) ),
    input_buffer_( user_input::max_input_size ),
    observer_(user_input::echo)
{
    on_ready_to_wait();
}

void user_input::set_observer(observer_type observer)
{
    observer_ = observer;
}

void user_input::on_ready_to_wait()
{
    // Read a line of input entered by the user.
    boost::asio::async_read_until(
        cli_handle_,
        input_buffer_,
        '\n',
        boost::bind( &user_input::on_input,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred ) );
}

void user_input::on_input( const boost::system::error_code& error, size_t length )
{
    std::string message;
    if (!error)
    {
        message.resize(length - 1);
        input_buffer_.sgetn(&message[0], length - 1);
        input_buffer_.consume(1); // Remove newline from input.
    }
    else if (error == boost::asio::error::not_found)
    {
        // Didn't get a newline. Send whatever we have.
        message.resize(length);
        input_buffer_.sgetn(&message[0], length);
    }
    else
    {
        return;
    }

    io_context_.post(boost::bind(observer_, boost::move(message)));
    on_ready_to_wait();
}

void user_input::echo(std::string message)
{
    std::cout << " > " << message << std::endl;
}

}  // end namespace evilquinn