
#include <asio/asio_context.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <cigsmoke/smoker.hpp>
#include <cigsmoke/table.hpp>
#include <iostream>
#include <signal_handler/signal_handler.hpp>
#include <thread>
#include <vector>

int main()
{
    evilquinn::register_signal_handler();
    auto asio = evilquinn::asio_context::get();

    std::shared_ptr<evilquinn::cig_smokers::table> table =
        std::make_shared<evilquinn::cig_smokers::table>( asio );
    const auto materials = std::vector<evilquinn::cig_smokers::material>{
        evilquinn::cig_smokers::material::tobacco,
        evilquinn::cig_smokers::material::papers,
        evilquinn::cig_smokers::material::matches
    };
    std::vector<evilquinn::cig_smokers::smoker> smokers;
    for ( auto&& material : materials )
    {
        smokers.emplace_back( material, asio, table );
    }

    for ( auto&& smoker : smokers )
    {
        smoker.sit();
    }

    const size_t num_threads = 3;
    std::vector<std::thread> threads( num_threads );
    for ( auto&& thread : threads )
    {
        thread = std::thread( [&asio]() { asio->run(); } );
    }

    const boost::posix_time::seconds run_duration( 5 );
    boost::asio::deadline_timer run_timer( *asio, run_duration );
    run_timer.async_wait( [&smokers]( const boost::system::error_code& ec ) {
        if ( ec )
        {
            return;
        }

        for ( auto&& smoker : smokers )
        {
            smoker.quit_smoking();
        }
    } );

    for ( auto&& thread : threads )
    {
        thread.join();
    }
    for ( auto&& smoker : smokers )
    {
        std::cout << smoker.to_string() << std::endl;
    }

    return 0;
}
