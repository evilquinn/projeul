#include <boost/stacktrace.hpp>
#include <iostream>
#include <signal_handler.hpp>
#include <string.h>

namespace evilquinn
{
void signal_handler( int sig_num, siginfo_t* sig_info, void* /*data*/ )
{
    std::cout << boost::stacktrace::stacktrace() << std::endl;

    if ( sig_num != 0 )
    {
        std::cout << "signal   : " << sig_num << std::endl;
        ::psignal( sig_num, "psignal  " );
    }
    if ( sig_info != nullptr )
    {
        ::psiginfo( sig_info, "psiginfo " );
    }

    // flush std::cout before exiting
    std::cout << std::endl;
    exit( sig_num );
}

void register_signal_handler()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_sigaction     = signal_handler;
    action.sa_flags         = SA_SIGINFO;
    sigaction( SIGTERM, &action, nullptr );
    sigaction( SIGINT, &action, nullptr );
    sigaction( SIGSEGV, &action, nullptr );
    sigaction( SIGABRT, &action, nullptr );
    sigaction( SIGFPE, &action, nullptr );
}

}  // end namespace evilquinn
