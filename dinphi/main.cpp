

#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <signal_handler.hpp>

static const auto dine_duration = std::chrono::seconds(2);
static const auto think_duration = std::chrono::seconds(1);
static const auto wait_duration = std::chrono::milliseconds(250);

static std::vector<std::timed_mutex> table(5);

class phi
{
public:
    phi(size_t id) :
        id_(id),
        offset_(id_*250)
    {}

    void dine()
    {
//        printf("%zu: sitting down\n", id_);
//        std::this_thread::sleep_for(offset_);
//        printf("%zu: ready\n", id_);
        size_t thinking_count = 0;

        size_t left_index = id_;
        size_t right_index = id_ == table.size()-1 ? 0 : id_+1;
        printf("%zu: sitting at %zu at table for %zu, left is %zu, right is %zu\n",
               id_,
               id_,
               table.size(),
               left_index,
               right_index);

        while ( true )
        {
            std::unique_lock<std::timed_mutex> left(
                table[left_index], std::defer_lock);
            std::unique_lock<std::timed_mutex> right(
                table[right_index], std::defer_lock);

//            printf("%zu: waiting for left\n", id_);
            left.try_lock_for(wait_duration);
//            printf("%zu: left: %d\n", id_, bool(left));
            if ( left )
            {
//                printf("%zu: waiting for right\n", id_);
                right.try_lock_for(wait_duration);
//                printf("%zu: right: %d\n", id_, bool(right));
            }

            if ( left && right )
            {
                thinking_count = 0;
                printf("%zu: DINING\n", id_);
                std::this_thread::sleep_for(dine_duration);
                printf("%zu: finished DINING\n", id_);
                left.unlock();
                right.unlock();
            }
            else
            {
                if ( left )
                {
                    left.unlock();
//                    printf("%zu: release left\n", id_);
                }
                if ( right )
                {
                    right.unlock();
//                    printf("%zu: release right\n", id_);
                }
                ++thinking_count;
                if ( thinking_count > 5 )
                {
                    printf("%zu: STARVING: %zu\n", id_, thinking_count);
                    std::this_thread::sleep_for(think_duration);
                    continue;
                }
            }

            printf("%zu: thinking: %zu\n", id_, thinking_count);
            std::this_thread::sleep_for(think_duration);
//            printf("%zu: finished thinking: %zu\n", id_, thinking_count);
        }
    }

private:
    size_t id_;
    const std::chrono::milliseconds offset_;
};

int main()
{
    evilquinn::register_signal_handler();
    std::vector<phi> phis
        { phi(0), phi(1), phi(2), phi(3), phi(4) };
    std::vector<std::thread> threads;
    for ( const auto& p : phis )
    {
        threads.emplace_back(&phi::dine, p);
    }
    for ( auto& t : threads )
    {
        t.join();
    }

    return 0;
}
