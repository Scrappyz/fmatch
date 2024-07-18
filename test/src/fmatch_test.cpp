#include <gtest/gtest.h>
#include "fmatch.hpp"

using namespace std;

namespace foption = fmatch::options;

TEST(match, matching)
{
    EXPECT_EQ(fmatch::match("potato/normal/go", "potato/normal/go"), true);
    EXPECT_EQ(fmatch::match("potato/normal/go", "potato/normal/god"), false);
    EXPECT_EQ(fmatch::match("potato/normal/god", "potato/normal/go"), false);
    EXPECT_EQ(fmatch::match("potato/nl/god", "potato/normal/go"), false);
}

TEST(match, asterisk)
{
    EXPECT_EQ(fmatch::match("potato/normal/go", "potato/n*l/go"), true);
    EXPECT_EQ(fmatch::match("potato/normal/go", "po*o/normal/go"), true);
    EXPECT_EQ(fmatch::match("my_project/main.cpp", "my_project/*.cpp"), true);
}

TEST(match, asterisk_end)
{
    EXPECT_EQ(fmatch::match("potato/normal/godude", "potato/normal/go*"), true);
}

TEST(match, multiple_asterisk)
{
    EXPECT_EQ(fmatch::match("potato/normal/godude", "po*o/n*l/go*"), true);
    EXPECT_EQ(fmatch::match("my_project/main.cpp", "my_project/*.*"), true);
    EXPECT_EQ(fmatch::match("my_project/test.txt", "my_project/*.*"), true);
}

TEST(match, asterisk_subdirectories)
{
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "po*o/n*l/go*"), true);
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "po*o/n*l/go*/"), false);
}

// TEST(match, asterisk_no_subdirectory)
// {
//     EXPECT_EQ(fmatch::match("potato/normal/godude", "potato/normal/*/"), true);
//     EXPECT_EQ(fmatch::match("potato/normal/godude", "potato/normal/*"), true);
// }

TEST(match, asterisk_current_directory)
{
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "po*o/n*l/*/"), false);
    EXPECT_EQ(fmatch::match("potato/normal/godude/", "po*o/n*l/*/"), true);
}

TEST(match, any)
{
    EXPECT_EQ(fmatch::match("potato/normal/go", "p?tat?/no?mal/go"), true);
}

TEST(match, different_separators)
{
    EXPECT_EQ(fmatch::match("potato/normal\\go", "p?tat?\\no?mal/go", {foption::MatchAnySeparator}), true);
    EXPECT_EQ(fmatch::match("potato/normal\\godude", "po*o\\n*l/go*", {foption::MatchAnySeparator}), true);
}