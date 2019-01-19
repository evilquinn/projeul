
#include <boost/asio/post.hpp>
#include <mdinphi/table.hpp>
#include <thread>

table::table( const size_t size, evilquinn::asio_context::handle asio )
    : forks_( size ), size_( size ), asio_( asio ), serialiser_( *asio )
{
}

size_t table::on_the_right_of( const size_t pos )
{
    return pos == size_ - 1 ? 0 : pos + 1;
}

void table::get_forks( const size_t pos,
                       fork_handler on_success,
                       fork_handler on_failure )
{
    boost::asio::post( serialiser_,
                       std::bind( &table::get_forked,
                                  this,
                                  pos,
                                  std::move( on_success ),
                                  std::move( on_failure ) ) );
}

// static const std::chrono::milliseconds block_duration(20);

void table::get_forked( const size_t pos,
                        fork_handler on_success,
                        fork_handler on_failure )
{
    // std::this_thread::sleep_for(block_duration);
    const size_t left  = pos;
    const size_t right = on_the_right_of( pos );
    if ( !forks_[left] && !forks_[right] )
    {
        forks_[left]  = true;
        forks_[right] = true;
        boost::asio::post( *asio_, std::move( on_success ) );
    }
    else
    {
        boost::asio::post( *asio_, std::move( on_failure ) );
    }
}

void table::release_forks( const size_t pos )
{
    boost::asio::post( serialiser_,
                       std::bind( &table::release_forked, this, pos ) );
}

void table::release_forked( const size_t pos )
{
    // std::this_thread::sleep_for(block_duration);
    const size_t left  = pos;
    const size_t right = on_the_right_of( pos );

    forks_[left]  = false;
    forks_[right] = false;
}
