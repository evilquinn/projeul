
#include <iostream>
#include <string>
#include <sstream>
#include <cigsmoke/smoker.hpp>
#include <boost/asio/post.hpp>

evilquinn::cig_smokers::smoker::smoker(const material item,
                                       asio_context::handle asio,
                                       std::shared_ptr<table> table) :
    item_(item),
    asio_(asio),
    table_(table),
    smoke_timer_(*asio_),
    wait_timer_(*asio_),
    quit_smoking_(false),
    smoke_count_(0),
    wait_count_(0)
{
}

void evilquinn::cig_smokers::smoker::sit()
{
    boost::asio::post(*asio_, std::bind(&smoker::try_smoke, this));
}

void evilquinn::cig_smokers::smoker::quit_smoking()
{
    quit_smoking_ = true;
}

void evilquinn::cig_smokers::smoker::try_smoke()
{
    if ( quit_smoking_ )
    {
        return;
    }
    asio_context::job on_request_success =
        std::bind(&smoker::on_request_success, this);
    asio_context::job on_request_failure =
        std::bind(&smoker::on_request_failure, this);
    boost::asio::post(*asio_,
                      std::bind(&table::request_material_for,
                                std::ref(*table_),
                                item_,
                                std::move(on_request_success),
                                std::move(on_request_failure)));
}

void evilquinn::cig_smokers::smoker::smoke()
{
    std::cout << static_cast<int>(item_) << ": smoking" << std::endl;
    ++smoke_count_;
    static const boost::posix_time::milliseconds smoke_duration(100);
    smoke_timer_.expires_from_now(smoke_duration);
    smoke_timer_.async_wait([this]( const boost::system::error_code& ec )
    {
        if ( !ec )
        {
            boost::asio::post(*asio_,
                              [this](){ table_->on_smoking_done(); });
            boost::asio::post(*asio_,
                              [this](){ wait(); });

        }
    });
}

void evilquinn::cig_smokers::smoker::wait()
{
    std::cout << static_cast<int>(item_) << ": waiting" << std::endl;
    ++wait_count_;
    static const boost::posix_time::milliseconds wait_duration(100);
    wait_timer_.expires_from_now(wait_duration);
    wait_timer_.async_wait([this]( const boost::system::error_code& ec )
    {
        if ( !ec )
        {
            boost::asio::post(*asio_, [this](){ try_smoke(); });
        }
    });
}

void evilquinn::cig_smokers::smoker::on_request_success()
{
    boost::asio::post(*asio_, std::bind(&smoker::smoke, this));
}

void evilquinn::cig_smokers::smoker::on_request_failure()
{
    boost::asio::post(*asio_, std::bind(&smoker::wait, this));
}

std::string evilquinn::cig_smokers::smoker::to_string()
{
    std::ostringstream oss;
    oss << static_cast<int>(item_) << " smoked " << smoke_count_ << " time, waited " << wait_count_ << " times.";


    return oss.str();
}

