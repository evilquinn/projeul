

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <mutex>
#include <signal_handler.hpp>
#include <string>
#include <thread>
#include <vector>

static const auto dine_duration  = std::chrono::milliseconds( 2 );
static const auto think_duration = std::chrono::milliseconds( 2 );

static bool stop                        = false;
static const int number_of_philosophers = 5;
static std::vector<std::timed_mutex> table( number_of_philosophers );
static std::vector<size_t> counts( number_of_philosophers );

class phi
{
public:
    phi( size_t id ) : id_( id ) {}

    void eat()
    {
        const size_t left_index  = id_;
        const size_t right_index = id_ == table.size() - 1 ? 0 : id_ + 1;

        std::lock( table[left_index], table[right_index] );

        std::unique_lock<std::timed_mutex> left( table[left_index],
                                                 std::adopt_lock );
        std::unique_lock<std::timed_mutex> right( table[right_index],
                                                  std::adopt_lock );

        std::this_thread::sleep_for( dine_duration );
    }

    void think() { std::this_thread::sleep_for( think_duration ); }

    void dine()
    {
        while ( !stop )
        {
            ++counts[id_];
            eat();
            think();
        }
    }

private:
    size_t id_;
};

int main()
{
    evilquinn::register_signal_handler();
    std::vector<phi> phis;
    for ( size_t id = 0; id < number_of_philosophers; ++id )
    {
        phis.emplace_back( id );
    }
    std::vector<std::thread> threads;
    for ( const auto& p : phis )
    {
        threads.emplace_back( &phi::dine, p );
    }

    const auto run_duration = std::chrono::seconds( 10 );
    std::this_thread::sleep_for( run_duration );
    stop = true;

    for ( auto& t : threads )
    {
        t.join();
    }

    for ( size_t i = 0; i < counts.size(); ++i )
    {
        std::cout << "phi " << i << " ate and thought " << counts[i]
                  << " times." << std::endl;
    }

    return 0;
}
