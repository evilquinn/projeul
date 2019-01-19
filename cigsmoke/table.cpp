
#include <cigsmoke/table.hpp>
#include <boost/asio/post.hpp>

evilquinn::cig_smokers::table::table(asio_context::handle asio) :
    on_table_(2),
    asio_(asio),
    serialiser_(*asio_)
{
}


void evilquinn::cig_smokers::table::request_material_for
(
    material item,
    asio_context::job on_success,
    asio_context::job on_failure
)
{
    if ( item == material::tobacco )
    {
        boost::asio::post(*asio_, std::move(on_success));
    }
    else
    {
        boost::asio::post(*asio_, std::move(on_failure));
    }
}

void evilquinn::cig_smokers::table::on_smoking_done()
{
}
