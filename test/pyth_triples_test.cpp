#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <pyth_triples.hpp>

using ::testing::Eq;
using ::testing::Lt;
using ::testing::Not;

TEST( TripletTest, constructorWithCWorks )
{
    const size_t a = 3;
    const size_t b = 4;
    const size_t c = 5;
    pyth::triplet t(a,b,c);
    EXPECT_THAT(t.a, Eq(a));
    EXPECT_THAT(t.b, Eq(b));
    EXPECT_THAT(t.c, Eq(c));
}

TEST( TripletTest, constructorWorks )
{
    const size_t a = 3;
    const size_t b = 4;
    const size_t c = 5;
    pyth::triplet t(a,b);
    EXPECT_THAT(t.a, Eq(a));
    EXPECT_THAT(t.b, Eq(b));
    EXPECT_THAT(t.c, Eq(c));
}

TEST( TripletTest, constructorThrowsInvalidAB )
{
    const size_t a = 3;
    const size_t b = 6;
    EXPECT_THROW(pyth::triplet(a,b), pyth::triplet::invalid_argument);
}

TEST( TripletTest, constructorThrowsInvalidABC )
{
    const size_t a = 3;
    const size_t b = 4;
    const size_t c = 6;
    EXPECT_THROW(pyth::triplet(a,b,c), pyth::triplet::invalid_argument);
}

TEST( TripletTest, lessThanWorksExpected )
{
    pyth::triplet t(3,4,5);
    pyth::triplet u(4,3,5);
    pyth::triplet v(5,12,13);
    EXPECT_THAT ( t, Not(Lt(u)));
    EXPECT_THAT ( t, Lt(v));
}

TEST( TripletTest, triplet_tWorksAsExpected )
{
    pyth::triplet t(3,4,5);
    pyth::triplet u(4,3,5);
    pyth::triplets_t trips = { t, u };
    EXPECT_THAT ( trips.size(), Eq(1) );
    EXPECT_THAT ( *(trips.begin()), Not(Lt(t)));
    EXPECT_THAT ( *(trips.begin()), Not(Lt(u)));
}

