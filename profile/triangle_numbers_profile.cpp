#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <triangle_numbers.hpp>

using ::testing::Eq;

#define TRIANGLE_NUMBERS_PROFILE_NUMBER 40000

class TriangleNumbersProfile : public ::testing::Test
{
protected:
    TriangleNumbersProfile() :
        triangles_(TRIANGLE_NUMBERS_PROFILE_NUMBER)
    {}
    ~TriangleNumbersProfile(){}

    virtual void SetUp(){}
    virtual void TearDown(){}

    triangle_numbers triangles_;
};

TEST_F(TriangleNumbersProfile, profileTriangleNumbersGetTerm)
{
    for(size_t i = 1; i <= TRIANGLE_NUMBERS_PROFILE_NUMBER; ++i)
    {
        size_t result = triangles_.get_term(i);
    }
}

TEST_F(TriangleNumbersProfile, profileTriangleNumbersCalcTriangleForTerm)
{
    for(size_t i = 1; i <= TRIANGLE_NUMBERS_PROFILE_NUMBER; ++i)
    {
        size_t result = triangle_numbers::calc_triangle_number_for_term(i);
    }
}
