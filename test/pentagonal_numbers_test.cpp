#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <known_primes.hpp>
#include <pentagonal_numbers.hpp>

using ::testing::Eq;

class PentagonalNumbersTest : public ::testing::Test
{
protected:
    PentagonalNumbersTest() {}
    ~PentagonalNumbersTest() override = default;
};

TEST_F( PentagonalNumbersTest, checkFirstTenPentagonalNumbers )
{
    std::set<size_t> known_pentagonals = { 1,  5,  12, 22,  35,
                                           51, 70, 92, 117, 145 };
    pentagonal_numbers pentagonals( known_pentagonals.size() );
    pentagonals.print();

    for ( size_t i = 1; i <= 145; ++i )
    {
        ASSERT_THAT(
            pentagonals.is_pentagonal( i ),
            Eq( known_pentagonals.find( i ) != known_pentagonals.end() ) );
    }

    auto it  = known_pentagonals.begin();
    size_t i = 1;
    while ( it != known_pentagonals.end() )
    {
        ASSERT_EQ( *it, pentagonals.get_term( i ) );
        ++it;
        ++i;
    }
}
