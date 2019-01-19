
#include <cigsmoke/table.hpp>
#include <boost/asio/post.hpp>

evilquinn::cig_smokers::table::table(asio_context::handle asio) :
    on_table_(2),
    asio_(asio),
    serialiser_(*asio_),
    helper_(asio_)
{
    boost::asio::post(*asio_, std::bind(&table::on_smoking_done, this));
}


void evilquinn::cig_smokers::table::request_material_for
(
    material item,
    asio_context::job on_success,
    asio_context::job on_failure
)
{
    if ( !on_table_[0] || item == on_table_[0] ||
         !on_table_[1] || item == on_table_[1] )
    {
        boost::asio::post(*asio_, std::move(on_failure));
    }
    else
    {
        remove_materials();
        boost::asio::post(*asio_, std::move(on_success));
    }
}

void evilquinn::cig_smokers::table::on_smoking_done()
{
    boost::asio::post(*asio_, [this]()
    {
        helper_.replace_materials(std::bind(&table::provide_materials,
                                            this,
                                            std::placeholders::_1,
                                            std::placeholders::_2));
    });
}

void evilquinn::cig_smokers::table::remove_materials()
{
    on_table_[0] = boost::none;
    on_table_[1] = boost::none;
}

void evilquinn::cig_smokers::table::provide_materials(const material m1,
                                                      const material m2)
{
    on_table_[0] = m1;
    on_table_[1] = m2;
}
