
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <signal_handler.hpp>

using ::testing::Eq;

TEST (signalHandlerTest, testRaisedSignalCausesExit)
{
    ASSERT_EXIT( raise(SIGINT),
                 ::testing::ExitedWithCode(SIGINT),
                 "Interrupt" );
}

int main( int argc, char** argv )
{
    testing::InitGoogleMock( &argc, argv );
    evilquinn::register_signal_handler();

    return RUN_ALL_TESTS();
}
