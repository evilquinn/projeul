

#include <string>
#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace evilquinn
{
class user_input
{
public:
    static const size_t max_input_size = 256;
    typedef boost::function<void(std::string)> observer_type;
    explicit user_input( boost::asio::io_context& io_context );
    void set_observer(observer_type observer);

private:
    void on_ready_to_wait();

    void on_input( const boost::system::error_code& error, size_t length );

    static void echo(std::string message);

    boost::asio::io_context& io_context_;
    boost::asio::posix::stream_descriptor cli_handle_;
    boost::asio::streambuf input_buffer_;
    observer_type observer_;
};

}  // end namespace evilquinn