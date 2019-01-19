

#include <iostream>
#include <signal_handler.hpp>
#include <mdinphi/table.hpp>
#include <mdinphi/diner.hpp>
#include <asio_context.hpp>
#include <vector>
#include <thread>
#include <functional>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    evilquinn::register_signal_handler();
    auto asio = evilquinn::asio_context::get();

    const auto num_diners = size_t{5};
    auto dining_table = table{num_diners, asio};

    auto diners = std::vector<diner>{};
    for ( size_t i = 0; i < num_diners; ++i )
    {
        diners.emplace_back(i,
                            asio,
                            std::bind(&table::get_forks,
                                      std::ref(dining_table),
                                      std::placeholders::_1,
                                      std::placeholders::_2,
                                      std::placeholders::_3),
                            std::bind(&table::release_forks,
                                      std::ref(dining_table),
                                      std::placeholders::_1));
    }

    for ( auto& d : diners )
    {
        asio->post(std::bind(&diner::dine,
                             std::ref(d)));

    }

    boost::asio::deadline_timer stop_diners(*asio,
                                            boost::posix_time::seconds(5));
    stop_diners.async_wait([&]( const boost::system::error_code& )
                           {
                               for ( auto& d : diners )
                               {
                                   d.stop_dining();
                               }
                           });

    std::vector<std::thread> thread_pool;
    const size_t num_threads = 5;
    for ( size_t i = 0; i < num_threads; ++i )
    {
        thread_pool.emplace_back([&asio]()
        {
            asio->run();
        });
    }

    for ( auto& thread : thread_pool )
    {
        thread.join();
    }

    for ( auto& d : diners )
    {
        std::cout << d.to_string() << std::endl;
    }

    return 0;
}
