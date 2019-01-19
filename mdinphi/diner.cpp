
#include <iostream>
#include <sstream>
#include <mdinphi/diner.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

static const boost::posix_time::milliseconds eat_duration(234);
static const boost::posix_time::milliseconds think_duration(123);

diner::diner(const size_t pos,
             evilquinn::asio_context::handle asio,
             get_forks_handler get_forks,
             release_forks_handler release_forks) :
    pos_(pos),
    asio_(asio),
    eating_timer_(*asio),
    thinking_timer_(*asio),
    get_forks_(get_forks),
    release_forks_(release_forks),
    still_dining_(true),
    eating_count_(0),
    thinking_count_(0),
    contention_count_(0)
{
}

void diner::dine()
{
    if ( still_dining_ )
    {
        fork_handler on_success = std::bind(&diner::on_fork_success, this);
        fork_handler on_fail = std::bind(&diner::on_fork_fail, this);
        asio_->post(std::bind(get_forks_,
                              pos_,
                              on_success,
                              on_fail));
    }
}

void diner::eat()
{
    std::cout << pos_ << ": eating!" << std::endl;
    ++eating_count_;
    eating_timer_.expires_from_now(eat_duration);
    eating_timer_.async_wait([this]( const boost::system::error_code& e )
    {
        if ( !e )
        {
            this->asio_->post(std::bind(this->release_forks_, this->pos_));
            this->asio_->post(std::bind(&diner::think, this));
        }
    });
}

void diner::contention()
{
    ++contention_count_;
    think();
}

void diner::think()
{
    std::cout << pos_ << ": thinking!" << std::endl;
    ++thinking_count_;
    thinking_timer_.expires_from_now(think_duration);
    thinking_timer_.async_wait([this]( const boost::system::error_code& e )
    {
        if ( !e )
        {
            this->dine();
        }
    });
}

void diner::on_fork_success()
{
    asio_->post(std::bind(&diner::eat, this));
}

void diner::on_fork_fail()
{
    asio_->post(std::bind(&diner::contention, this));
}

void diner::stop_dining()
{
    still_dining_ = false;
}

std::string diner::to_string()
{
    std::ostringstream oss;
    oss << pos_ << " has eaten " << eating_count_ << " times, "
        << "thought " << thinking_count_ << " times, "
        << contention_count_ << " times of which were from contention.";
    return oss.str();
}
