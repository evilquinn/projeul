#include <boost/stacktrace.hpp>
#include <iostream>
#include <signal_handler.hpp>

namespace evilquinn
{
void signal_handler( int sig_num, siginfo_t* sig_info, void* /*data*/ )
{
    std::cout << boost::stacktrace::stacktrace() << std::endl;

    if ( sig_num != 0 )
    {
        std::cout << "signal   : " << sig_num << std::endl;
    }
    if ( sig_info != nullptr )
    {
        std::cout << "si_signo : " << sig_info->si_signo << "\n"
                  << "si_errno : " << sig_info->si_errno << "\n"
                  << "si_code  : " << sig_info->si_code << "\n";
        switch ( sig_num )
        {
        case SIGILL:   // fall through
        case SIGFPE:   // fall through
        case SIGSEGV:  // fall through
        case SIGBUS:   // fall through
        case SIGTRAP:  // fall through
        {
            std::cout << "si_addr  : " << sig_info->si_addr << "\n";
            break;
        }
        default:
        {
            // no op
        }  // end case
        }  // end switch

        ::psignal( sig_num, "psignal  " );
        ::psiginfo( sig_info, "psiginfo " );
    }

    exit( sig_num );
}

void register_signal_handler()
{
    struct sigaction action = { nullptr };
    action.sa_sigaction     = signal_handler;
    action.sa_flags         = SA_SIGINFO;
    sigaction( SIGTERM, &action, nullptr );
    sigaction( SIGINT, &action, nullptr );
    sigaction( SIGSEGV, &action, nullptr );
    sigaction( SIGABRT, &action, nullptr );
    sigaction( SIGFPE, &action, nullptr );
}

}  // end namespace evilquinn
