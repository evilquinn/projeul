#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <hexagonal_numbers.hpp>

using ::testing::Eq;

class HexagonalNumbersTest : public ::testing::Test
{
protected:
    HexagonalNumbersTest() {}
    ~HexagonalNumbersTest() override = default;
};

TEST_F( HexagonalNumbersTest, checkFirstFiveHexagonalNumbers )
{
    std::set<size_t>  known_hexagonals = { 1, 6, 15, 28, 45 };
    hexagonal_numbers hexagonals( known_hexagonals.size() );

    for ( size_t i = 1; i <= 45; ++i )
    {
        ASSERT_THAT(
            hexagonals.is_hexagonal( i ),
            Eq( known_hexagonals.find( i ) != known_hexagonals.end() ) );
    }

    auto   it = known_hexagonals.begin();
    size_t i  = 1;
    while ( it != known_hexagonals.end() )
    {
        ASSERT_EQ( *it, hexagonals.get_term( i ) );
        ++it;
        ++i;
    }
}
