#include <boost/asio.hpp>
#include <iostream>
#include <vector>

void resolve_handler(
    const boost::system::error_code& ec,
    boost::asio::ip::tcp::resolver::results_type results)
{
    if ( ec )
    {
        std::cout << "resolve_handler error: " << ec << "\n";
        return;
    }

    std::vector<boost::asio::ip::tcp::endpoint> superset(results.begin(), results.end());

    superset.emplace_back(boost::asio::ip::make_address("1.2.3.4"), 123);
    superset.emplace_back(boost::asio::ip::make_address("3.4.5.6"), 345);

    for ( auto&& endpoint : superset )
    {
        std::cout << endpoint << std::endl;
    }
}

int main()
{
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);

    resolver.async_resolve("www.google.com", "http", resolve_handler);

    io_service.run();
    return 0;
}
