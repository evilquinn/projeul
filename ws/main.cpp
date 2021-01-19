
#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

class cli
{
public:
    cli(boost::asio::io_context& io_context) :
        io_context_(io_context)
    {}
    typedef boost::function<void(boost::system::error_code const&, const std::string&)> async_read_callback;
    void async_wait(async_read_callback callback)
    {

    }
private:
    boost::asio::io_context& io_context_;
};

std::string read_from_user(const std::string& prompt = "command> ")
{
    std::string line;
    std::cout << prompt;
    std::cin >> line;
    return line;
}

void main_loop()
{
    while(1)
    {
        std::string command = read_from_user();
        if ( command == "quit" )
        {
            std::cout << "quitting...\n";
            break;
        }
        else if ( command == "connect" )
        {
            std::cout << "yeah, right...\n";
        }
        else if ( command == "help" )
        {
            std::cout
                << "\nCommand List:\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << std::endl;
        }
        else
        {
            std::cout << "unrecognised command: " << command << "\n";
        }
    }
}

int main()
{

    std::cout << "hello" << std::endl;
    main_loop();
    return 0;
}
