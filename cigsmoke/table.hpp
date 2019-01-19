
#ifndef CIGSMOKE_TABLE_HPP
#define CIGSMOKE_TABLE_HPP

#include <vector>
#include <boost/optional.hpp>
#include <cigsmoke/material.hpp>
#include <asio/asio_context.hpp>

namespace evilquinn
{
namespace cig_smokers
{

class table
{
public:
    table();
    void request_material_for(material item,
                              asio_context::job on_success,
                              asio_context::job on_failure);
    void on_smoking_done();

private:
    std::vector< boost::optional<material> > on_table_;
};

} // end namespace cig_smokers
} // end namespace evilquinn

#endif // CIGSMOKE_TABLE_HPP

