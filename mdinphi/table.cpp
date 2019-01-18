
#include <mdinphi/table.hpp>

table::table(const size_t size,
             evilquinn::asio_context::handle asio) :
    forks_(size),
    size_(size),
    asio_(asio)
{
}

size_t table::on_the_right_of(const size_t pos)
{
    return pos == size_ - 1 ? 0 : pos + 1;
}

void table::get_forked(const size_t pos,
                       fork_handler on_success,
                       fork_handler on_failure)
{
    const size_t left = pos;
    const size_t right = on_the_right_of(pos);
    if ( !forks_[left] && !forks_[right] )
    {
        forks_[left] = true;
        forks_[right] = true;
        on_success();
    }
    else
    {
        on_failure();
    }
}

void table::release_forks(const size_t pos)
{
    const size_t left = pos;
    const size_t right = on_the_right_of(pos);

    forks_[left] = false;
    forks_[right] = false;
}

