
#include <boost/asio/post.hpp>
#include <boost/random.hpp>
#include <boost/random/uniform_int.hpp>
#include <cigsmoke/agent.hpp>

evilquinn::cig_smokers::agent::agent( asio_context::handle asio )
    : asio_( asio )
{
}

void evilquinn::cig_smokers::agent::replace_materials(
    provide_materials_job provide_materials )
{
    static boost::random::mt19937 rng(
        static_cast<unsigned int>( std::time( nullptr ) ) );
    static boost::random::uniform_int_distribution<> dist( 0, 2 );
    material m0 = static_cast<material>( dist( rng ) );
    material m1 = static_cast<material>( dist( rng ) );
    while ( m1 == m0 )
    {
        m1 = static_cast<material>( dist( rng ) );
    }

    boost::asio::post( *asio_,
                       std::bind( std::move( provide_materials ), m0, m1 ) );
}
