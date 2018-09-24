#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <unique_cptr.hpp>

using ::testing::Eq;
using ::testing::StrEq;

TEST( UniqueCptrTest, testMemoryAutomaticallyDeleted )
{
    // this test probably won't ever fail, but it's purpose is to ensure that
    // valgrind will report leaked memory in the event our unique_cptr
    // class doesn't work appropriately
    const char* string_literal = "string_literal";
    auto auto_string_literal = make_unique_cptr(strdup(string_literal));

    EXPECT_THAT ( string_literal, StrEq(auto_string_literal.get()) );
}

TEST( UniqueCptrTest, testMoveConstructorWorks )
{
    const char* string_literal = "string_literal";
    auto auto_string_literal = make_unique_cptr(strdup(string_literal));

    auto moved_string_literal(boost::move(auto_string_literal));

    EXPECT_THAT ( auto_string_literal.get(), Eq(nullptr) );
    EXPECT_THAT ( string_literal, StrEq(moved_string_literal.get()) );
}

TEST( UniqueCptrTest, testMoveAssigmentWorks )
{
    const char* string_literal = "string_literal";
    auto auto_string_literal = make_unique_cptr(strdup(string_literal));

    auto moved_string_literal(boost::move(auto_string_literal));

    auto_string_literal = boost::move(moved_string_literal);

    EXPECT_THAT ( moved_string_literal.get(), Eq(nullptr) );
    EXPECT_THAT ( string_literal, StrEq(auto_string_literal.get()) );
}
