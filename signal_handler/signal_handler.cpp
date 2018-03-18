#include <signal_handler.hpp>
#include <iostream>
#include <boost/stacktrace.hpp>

namespace evilquinn {

void signal_handler(int sig_num, siginfo_t* sig_info, void* data)
{
    std::cout << boost::stacktrace::stacktrace() << std::endl;

    if ( sig_num )
    {
        std::cout << "Signal:     " << sig_num << std::endl;
    }

    exit(sig_num);
}

void register_signal_handler()
{
    struct sigaction action;
    action.sa_sigaction = signal_handler;
    action.sa_flags     = SA_SIGINFO;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT,  &action, NULL);
    sigaction(SIGSEGV, &action, NULL);
    sigaction(SIGABRT, &action, NULL);
}

} // end namespace evilquinn
