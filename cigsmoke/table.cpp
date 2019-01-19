
#include <cigsmoke/table.hpp>

evilquinn::cig_smokers::table::table() :
    on_table_(2)
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
        on_success();
    }
    else
    {
        on_failure();
    }
}

void evilquinn::cig_smokers::table::on_smoking_done()
{
}
