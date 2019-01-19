
#ifndef CIGSMOKE_TABLE_HPP
#define CIGSMOKE_TABLE_HPP

#include <vector>
#include <boost/optional.hpp>
#include <cigsmoke/material.hpp>
#include <cigsmoke/agent.hpp>
#include <asio/asio_context.hpp>
#include <boost/asio/io_context_strand.hpp>

namespace evilquinn
{
namespace cig_smokers
{

class table
{
public:
    table(asio_context::handle asio);
    void request_material_for(material item,
                              asio_context::job on_success,
                              asio_context::job on_failure);
    void on_smoking_done();

private:
    void remove_materials();
    void provide_materials(material m1, material m2);
    std::vector< boost::optional<material> > on_table_;
    asio_context::handle asio_;
    boost::asio::io_context::strand serialiser_;
    agent helper_;
};

} // end namespace cig_smokers
} // end namespace evilquinn

#endif // CIGSMOKE_TABLE_HPP

