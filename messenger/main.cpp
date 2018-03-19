

#include <iostream>
#include <asio_context.hpp>
#include <signal_handler.hpp>


#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace evilquinn
{

class cli
{
public:
    static const size_t max_input_size = 256;
    cli(boost::asio::io_context& io_context) :
        cli_handle_(io_context, ::dup(STDIN_FILENO)),
        input_buffer_(cli::max_input_size)
    {
        on_ready();
    }

private:
    void on_ready()
    {
        // Read a line of input entered by the user.
        std::cout << "Enter command: " << std::endl;
        boost::asio::async_read_until(cli_handle_, input_buffer_, '\n',
        boost::bind(&cli::on_input, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
    }

    void on_input(const boost::system::error_code& error,
                  size_t length)
    {
        if (!error)
        {
            std::istream is(&input_buffer_);
            std::string s;
            is >> s;
            std::cout << "RECEIVED: " << s << std::endl;

            if ( s != "q" )
            {
                on_ready();
            }
            else
            {
                std::cout << "quitting!" << std::endl;
            }
        }
        else
        {
            std::cout << "ERROR: " << error << std::endl;
            cli_handle_.close();
        }
    }

    boost::asio::posix::stream_descriptor cli_handle_;
    boost::asio::streambuf                input_buffer_;

};

} // end namespace evilquinn

int main(int argc, char* argv[])
{
    auto asio_context = evilquinn::asio_context::get();
    evilquinn::register_signal_handler();

    std::cout << "hello" << std::endl;

    evilquinn::cli handle_cli(*asio_context);

    asio_context->run();

    std::cout << "All done." << std::endl;
    return 0;
}
