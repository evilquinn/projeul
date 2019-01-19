#ifndef MDINPHI_DINER_HPP
#define MDINPHI_DINER_HPP

#include <asio_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <mdinphi/table.hpp>

class diner
{
public:
    diner( size_t pos,
           evilquinn::asio_context::handle asio,
           get_forks_handler get_forks,
           release_forks_handler release_forks );

    void dine();
    void stop_dining();
    std::string to_string();

private:
    void eat();
    void think();

    void on_fork_success();
    void on_fork_fail();

    size_t pos_;
    evilquinn::asio_context::handle asio_;
    boost::asio::deadline_timer eating_timer_;
    boost::asio::deadline_timer thinking_timer_;
    get_forks_handler get_forks_;
    release_forks_handler release_forks_;
    bool still_dining_;
    size_t eating_count_;
    size_t thinking_count_;
};
#endif  // MDINPHI_DINER_HPP
