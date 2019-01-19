
#ifndef CIGSMOKE_AGENT_HPP
#define CIGSMOKE_AGENT_HPP

#include <asio/asio_context.hpp>
#include <cigsmoke/material.hpp>

namespace evilquinn
{
namespace cig_smokers
{
class agent
{
public:
    agent( asio_context::handle asio );
    using provide_materials_job = std::function<void( material, material )>;
    void replace_materials( provide_materials_job provide_materials );

private:
    asio_context::handle asio_;
};

}  // end namespace cig_smokers
}  // end namespace evilquinn

#endif  // CIGSMOKE_AGENT_HPP
