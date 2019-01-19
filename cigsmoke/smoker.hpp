
#ifndef CIGSMOKE_SMOKER_HPP
#define CIGSMOKE_SMOKER_HPP

#include <boost/asio/deadline_timer.hpp>
#include <cigsmoke/material.hpp>
#include <cigsmoke/table.hpp>

namespace evilquinn
{
namespace cig_smokers
{
class smoker
{
public:
    smoker( material item,
            asio_context::handle asio,
            std::shared_ptr<table> table );

    void sit();
    void quit_smoking();
    std::string to_string();

private:
    void try_smoke();
    void smoke();
    void wait();
    void on_request_success();
    void on_request_failure();
    material item_;
    asio_context::handle asio_;
    std::shared_ptr<table> table_;
    boost::asio::deadline_timer smoke_timer_;
    boost::asio::deadline_timer wait_timer_;
    bool quit_smoking_;
    size_t smoke_count_;
    size_t wait_count_;
};

}  // end namespace cig_smokers
}  // end namespace evilquinn

#endif  // CIGSMOKE_SMOKER_HPP
