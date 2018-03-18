
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <asio_context.hpp>
#include <boost/bind.hpp>
#include <signal_handler.hpp>

static int run_all_tests(int* argc, char** argv)
{
    // Since Google Mock depends on Google Test, InitGoogleMock() is
    // also responsible for initializing Google Test.  Therefore there's
    // no need for calling testing::InitGoogleTest() separately.
    testing::InitGoogleMock(argc, argv);
    return RUN_ALL_TESTS();
}

int main(int argc, char** argv)
{
    evilquinn::register_signal_handler();

    auto asio_context = evilquinn::asio_context::get();
    asio_context->post(boost::bind(run_all_tests, &argc, argv));
    asio_context->run();

    return 0;
}
