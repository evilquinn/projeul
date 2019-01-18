
#ifndef MDINPHI_TABLE_HPP
#define MDINPHI_TABLE_HPP

#include <functional>
#include <vector>
#include <asio_context.hpp>

using fork_handler = std::function<void()>;
using get_forks_handler = std::function<void(size_t, fork_handler, fork_handler)>;
using release_forks_handler = std::function<void(size_t)>;

class table
{
public:
    table(size_t size,
          evilquinn::asio_context::handle asio);
    void get_forked(size_t pos, fork_handler on_success, fork_handler on_fail);
    void release_forks(size_t pos);
private:
    size_t on_the_right_of(size_t pos);
    std::vector<char> forks_;
    size_t size_;
    evilquinn::asio_context::handle asio_;
};


#endif  // MDINPHI_TABLE_HPP
