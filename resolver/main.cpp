#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <thread>
#include <chrono>


boost::asio::io_service io_service;
boost::asio::ip::tcp::socket sock(io_service);

void connect_handler(const boost::system::error_code& ec,
                     const boost::asio::ip::tcp::endpoint& endpoint)
{
    if ( ec )
    {
        std::cout << "connect_handler error connecting to " << endpoint
                  << " : " << ec << " : " << ec.category().message(ec.value());
        return;
    }

    std::cout << "connected to " << endpoint << std::endl;

    sock.send(boost::asio::buffer("jimmy\n"));

}
void resolve_handler(
    const boost::system::error_code& ec,
    boost::asio::ip::tcp::resolver::results_type results)
{
    if ( ec )
    {
        std::cout << "resolve_handler error: " << ec << " : " << ec.category().message(ec.value());
        return;
    }

    std::cout << "sleep fo 10s, disconnect internet so \"resolved\" ips will fail" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::vector<boost::asio::ip::tcp::endpoint> superset(results.begin(), results.end());

    superset.emplace_back(boost::asio::ip::make_address("127.0.0.1"), 123);
    superset.emplace_back(boost::asio::ip::make_address("127.0.0.1"), 3456);

    for ( auto&& endpoint : superset )
    {
        std::cout << endpoint << std::endl;
    }

    boost::asio::async_connect(sock, superset, connect_handler);
}

int main()
{
    boost::asio::ip::tcp::resolver resolver(io_service);

    resolver.async_resolve("www.gmail.com", "http", resolve_handler);

    io_service.run();
    return 0;
}
