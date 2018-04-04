
#include <gtest/gtest.h>

#include <signal_handler.hpp>

TEST( signalHandlerTest, testRaisedSignalCausesExit )
{
    ASSERT_EXIT(
        raise( SIGINT ), ::testing::ExitedWithCode( SIGINT ), "Interrupt" );
}
