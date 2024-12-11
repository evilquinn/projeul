

#include <iostream>
#include <string>
#include <signal_handler.hpp>

#include <utility> // asio need this
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/function.hpp>
#include <boost/move/move.hpp>
#include <boost/thread.hpp>

namespace evilquinn
{
class cli
{
public:
    static const size_t max_input_size = 256;
    typedef boost::function<void(std::string)> observer_type;
    explicit cli( boost::asio::io_context& io_context ) :
        io_context_(io_context),
        cli_handle_( io_context_, ::dup(STDIN_FILENO) ),
        input_buffer_( cli::max_input_size ),
        observer_(cli::echo)
    {
        on_ready_to_wait();
    }

private:
    void on_ready_to_wait()
    {
        // Read a line of input entered by the user.
        boost::asio::async_read_until(
            cli_handle_,
            input_buffer_,
            '\n',
            boost::bind( &cli::on_input,
                         this,
                         boost::asio::placeholders::error,
                         boost::asio::placeholders::bytes_transferred ) );
    }

    void on_input( const boost::system::error_code& error, size_t length )
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

    static void echo(std::string message)
    {
        std::cout << " > " << message << std::endl;
    }

    boost::asio::io_context& io_context_;
    boost::asio::posix::stream_descriptor cli_handle_;
    boost::asio::streambuf input_buffer_;
    observer_type observer_;
};

}  // end namespace evilquinn

int main( int /*argc*/, char** /*argv*/ )
{
    boost::asio::io_context asio_context;
    evilquinn::register_signal_handler();

    std::cout << "hello" << std::endl;

    evilquinn::cli handle_cli( asio_context );
    //evilquinn::loggy l(asio_context);

    asio_context.run();

    std::cout << "All done." << std::endl;
    return 0;
}
