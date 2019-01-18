#ifndef ASIO_CONTEXT_HPP_
#define ASIO_CONTEXT_HPP_

#include <boost/asio/io_context.hpp>
#include <boost/shared_ptr.hpp>

namespace evilquinn
{
class asio_context
{
public:
    using handle = boost::shared_ptr<boost::asio::io_context>;
    static handle get();
};

}  // end namespace evilquinn

#endif  // ASIO_CONTEXT_HPP_
