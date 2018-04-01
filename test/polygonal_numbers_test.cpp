#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <known_primes.hpp>
#include <polygonal_numbers.hpp>

using ::testing::Eq;

class PolygonalNumbersTest : public ::testing::Test
{
protected:
    PolygonalNumbersTest() {}
    ~PolygonalNumbersTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F( PolygonalNumbersTest, checkFirstTenTriangleNumbers )
{
    std::set<size_t> known_polygonals = {
        1, 3, 6, 10, 15, 21, 28, 36, 45, 55
    };
    polygonal_numbers polygonals( known_polygonals.size(),
                                  polygonal_numbers::triangle );

    for ( size_t i = 1; i <= 55; ++i )
    {
        ASSERT_THAT(
            polygonals.is_in( i ),
            Eq( known_polygonals.find( i ) != known_polygonals.end() ) );
    }

    std::set<size_t>::iterator it = known_polygonals.begin();
    size_t                     i  = 1;
    while ( it != known_polygonals.end() )
    {
        ASSERT_EQ( *it, polygonals.get_term( i ) );
        ++it;
        ++i;
    }
}

TEST_F( PolygonalNumbersTest, checkFirstTenSqaureNumbers )
{
    std::set<size_t> known_polygonals = {
        1, 4, 9, 16, 25, 36, 49, 64, 81, 100
    };
    polygonal_numbers polygonals( known_polygonals.size(),
                                  polygonal_numbers::square );

    for ( size_t i = 1; i <= 100; ++i )
    {
        ASSERT_THAT(
            polygonals.is_in( i ),
            Eq( known_polygonals.find( i ) != known_polygonals.end() ) );
    }

    std::set<size_t>::iterator it = known_polygonals.begin();
    size_t                     i  = 1;
    while ( it != known_polygonals.end() )
    {
        ASSERT_EQ( *it, polygonals.get_term( i ) );
        ++it;
        ++i;
    }
}

TEST_F( PolygonalNumbersTest, checkFirstTenPentagonalNumbers )
{
    std::set<size_t> known_polygonals = { 1,  5,  12, 22,  35,
                                          51, 70, 92, 117, 145 };
    polygonal_numbers polygonals( known_polygonals.size(),
                                  polygonal_numbers::pentagonal );

    for ( size_t i = 1; i <= 145; ++i )
    {
        ASSERT_THAT(
            polygonals.is_in( i ),
            Eq( known_polygonals.find( i ) != known_polygonals.end() ) );
    }

    std::set<size_t>::iterator it = known_polygonals.begin();
    size_t                     i  = 1;
    while ( it != known_polygonals.end() )
    {
        ASSERT_EQ( *it, polygonals.get_term( i ) );
        ++it;
        ++i;
    }
}

TEST_F( PolygonalNumbersTest, checkFirstTenHexagonalNumbers )
{
    std::set<size_t> known_polygonals = { 1,  6,  15,  28,  45,
                                          66, 91, 120, 153, 190 };
    polygonal_numbers polygonals( known_polygonals.size(),
                                  polygonal_numbers::hexagonal );

    for ( size_t i = 1; i <= 190; ++i )
    {
        ASSERT_THAT(
            polygonals.is_in( i ),
            Eq( known_polygonals.find( i ) != known_polygonals.end() ) );
    }

    std::set<size_t>::iterator it = known_polygonals.begin();
    size_t                     i  = 1;
    while ( it != known_polygonals.end() )
    {
        ASSERT_EQ( *it, polygonals.get_term( i ) );
        ++it;
        ++i;
    }
}

TEST_F( PolygonalNumbersTest, checkFirstTenHeptagonalNumbers )
{
    std::set<size_t> known_polygonals = { 1,  7,   18,  34,  55,
                                          81, 112, 148, 189, 235 };
    polygonal_numbers polygonals( known_polygonals.size(),
                                  polygonal_numbers::heptagonal );

    for ( size_t i = 1; i <= 235; ++i )
    {
        ASSERT_THAT(
            polygonals.is_in( i ),
            Eq( known_polygonals.find( i ) != known_polygonals.end() ) );
    }

    std::set<size_t>::iterator it = known_polygonals.begin();
    size_t                     i  = 1;
    while ( it != known_polygonals.end() )
    {
        ASSERT_EQ( *it, polygonals.get_term( i ) );
        ++it;
        ++i;
    }
}

TEST_F( PolygonalNumbersTest, checkFirstTenOctagonalNumbers )
{
    std::set<size_t> known_polygonals = { 1,  8,   21,  40,  65,
                                          96, 133, 176, 225, 280 };
    polygonal_numbers polygonals( known_polygonals.size(),
                                  polygonal_numbers::octagonal );

    for ( size_t i = 1; i <= 280; ++i )
    {
        ASSERT_THAT(
            polygonals.is_in( i ),
            Eq( known_polygonals.find( i ) != known_polygonals.end() ) );
    }

    std::set<size_t>::iterator it = known_polygonals.begin();
    size_t                     i  = 1;
    while ( it != known_polygonals.end() )
    {
        ASSERT_EQ( *it, polygonals.get_term( i ) );
        ++it;
        ++i;
    }
}
