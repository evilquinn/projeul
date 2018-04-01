#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <known_primes.hpp>
#include <triangle_numbers.hpp>

using ::testing::Eq;

class TriangleNumbersTest : public ::testing::Test
{
protected:
    TriangleNumbersTest() {}
    ~TriangleNumbersTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F( TriangleNumbersTest, checkFirstTenTriangleNumbers )
{
    std::set<size_t> known_triangles = {
        1, 3, 6, 10, 15, 21, 28, 36, 45, 55
    };
    triangle_numbers triangles( known_triangles.size() );

    for ( size_t i = 1; i <= 55; ++i )
    {
        ASSERT_THAT(
            triangles.is_triangle( i ),
            Eq( known_triangles.find( i ) != known_triangles.end() ) );
    }

    std::set<size_t>::iterator it = known_triangles.begin();
    size_t                     i  = 1;
    while ( it != known_triangles.end() )
    {
        ASSERT_EQ( *it, triangles.get_term( i ) );
        ++it;
        ++i;
    }
}
