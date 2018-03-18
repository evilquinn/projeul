#ifndef ASIO_CONTEXT_HPP_
#define ASIO_CONTEXT_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/asio/io_context.hpp>

namespace evilquinn
{

class asio_context
{
public:
    static boost::shared_ptr<boost::asio::io_context> get();
};

} // end namespace evilquinn

#endif // ASIO_CONTEXT_HPP_
