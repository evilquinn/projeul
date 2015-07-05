#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <triangle_numbers/triangle_numbers.hpp>
#include <known_primes.hpp>

using ::testing::Eq;

class TriangleNumbersTest : public ::testing::Test
{
protected:
    TriangleNumbersTest(){}
    ~TriangleNumbersTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(TriangleNumbersTest, checkFirstTenTriangleNumbers)
{
    size_t terms = 10;
    triangle_numbers triangles(terms);

    ASSERT_THAT(true, Eq(triangles.is_triangle(1)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(3)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(6)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(10)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(15)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(21)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(28)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(36)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(45)));
    ASSERT_THAT(true, Eq(triangles.is_triangle(55)));
}
