
#include <asio_context.hpp>
#include <boost/make_shared.hpp>

boost::shared_ptr<boost::asio::io_context> evilquinn::asio_context::get()
{
    static boost::shared_ptr<boost::asio::io_context> handle(
        boost::make_shared<boost::asio::io_context>());
    return handle;
}
