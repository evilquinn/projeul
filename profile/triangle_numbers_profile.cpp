#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <triangle_numbers.hpp>

#define TRIANGLE_NUMBERS_PROFILE_NUMBER 100000

class TriangleNumbersProfile : public ::testing::Test
{
protected:
    TriangleNumbersProfile()
        : triangles( new triangle_numbers( TRIANGLE_NUMBERS_PROFILE_NUMBER ) )
    {
    }
    ~TriangleNumbersProfile() override { delete triangles; }
    triangle_numbers* triangles;
};

TEST_F( TriangleNumbersProfile, profileTriangleNumbersGetTerm )
{
    size_t result;
    for ( size_t i = 1; i <= TRIANGLE_NUMBERS_PROFILE_NUMBER; ++i )
    {
        result = triangles->get_term( i );
    }
    if ( result != 0u )
    {
        // no op
    }
}

TEST_F( TriangleNumbersProfile, profileTriangleNumbersCalcTriangleForTerm )
{
    size_t result;
    for ( size_t i = 1; i <= TRIANGLE_NUMBERS_PROFILE_NUMBER; ++i )
    {
        result = triangle_numbers::calc_triangle_number_for_term( i );
    }
    if ( result != 0u )
    {
        // no op
    }
}
