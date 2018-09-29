

#include <asio_context.hpp>
#include <iostream>
#include <signal_handler.hpp>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace evilquinn
{
class cli
{
public:
    static const size_t max_input_size = 256;
    explicit cli( boost::asio::io_context& io_context )
        : cli_handle( io_context, fcntl( STDIN_FILENO, F_DUPFD_CLOEXEC ) ),
          input_buffer( cli::max_input_size )
    {
        on_ready_to_wait();
    }

private:
    void on_ready_to_wait()
    {
        // Read a line of input entered by the user.
        std::cout << "Enter command: " << std::flush;
        boost::asio::async_read_until(
            cli_handle,
            input_buffer,
            '\n',
            boost::bind( &cli::on_input,
                         this,
                         boost::asio::placeholders::error,
                         boost::asio::placeholders::bytes_transferred ) );
    }

    void on_input( const boost::system::error_code& error, size_t /*length*/ )
    {
        if ( !error )
        {
            std::string s;
            std::istream is( &input_buffer );
            is >> s;
            // eat the remaining newline
            input_buffer.consume( 1 );

            if ( s == "q" )
            {
                std::cout << "quitting!" << std::endl;
                return;
            }
            if ( s == "h" )
            {
                print_usage();
            }

            on_ready_to_wait();
        }
        else
        {
            std::cout << "ERROR: " << error << std::endl;
        }
    }

    void print_usage()
    {
        std::cout << "messenger help:\n"
                  << "\n"
                  << "    h    Print this message\n"
                  << "    q    Quit\n"
                  << std::endl;
    }

    boost::asio::posix::stream_descriptor cli_handle;
    boost::asio::streambuf input_buffer;
};

}  // end namespace evilquinn

int main( int /*argc*/, char** /*argv*/ )
{
    auto asio_context = evilquinn::asio_context::get();
    evilquinn::register_signal_handler();

    std::cout << "hello" << std::endl;

    evilquinn::cli handle_cli( *asio_context );

    asio_context->run();

    std::cout << "All done." << std::endl;
    return 0;
}
