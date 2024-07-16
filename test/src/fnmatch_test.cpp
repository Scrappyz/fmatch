#include <gtest/gtest.h>
#include "fnmatch.hpp"

using namespace std;

namespace foption = fnmatch::options;

TEST(match, matching)
{
    EXPECT_EQ(fnmatch::match("potato/normal/go", "potato/normal/go"), true);
    EXPECT_EQ(fnmatch::match("potato/normal/go", "potato/normal/god"), false);
    EXPECT_EQ(fnmatch::match("potato/normal/god", "potato/normal/go"), false);
    EXPECT_EQ(fnmatch::match("potato/nl/god", "potato/normal/go"), false);
}

TEST(match, asterisk)
{
    EXPECT_EQ(fnmatch::match("potato/normal/go", "potato/n*l/go"), true);
    EXPECT_EQ(fnmatch::match("potato/normal/go", "po*o/normal/go"), true);
    EXPECT_EQ(fnmatch::match("my_project/main.cpp", "my_project/*.cpp"), true);
}

TEST(match, asterisk_end)
{
    EXPECT_EQ(fnmatch::match("potato/normal/godude", "potato/normal/go*"), true);
}

TEST(match, multiple_asterisk)
{
    EXPECT_EQ(fnmatch::match("potato/normal/godude", "po*o/n*l/go*"), true);
    EXPECT_EQ(fnmatch::match("my_project/main.cpp", "my_project/*.*"), true);
    EXPECT_EQ(fnmatch::match("my_project/test.txt", "my_project/*.*"), true);
}

TEST(match, asterisk_subdirectories)
{
    EXPECT_EQ(fnmatch::match("potato/normal/godude/hello", "po*o/n*l/go*"), true);
    EXPECT_EQ(fnmatch::match("potato/normal/godude/hello", "po*o/n*l/go*/"), false);
}

TEST(match, asterisk_current_directory)
{
    EXPECT_EQ(fnmatch::match("potato/normal/godude/hello", "po*o/n*l/*/"), false);
    EXPECT_EQ(fnmatch::match("potato/normal/godude/", "po*o/n*l/*/"), true);
}

TEST(match, any)
{
    EXPECT_EQ(fnmatch::match("potato/normal/go", "p?tat?/no?mal/go"), true);
}

TEST(match, different_separators)
{
    EXPECT_EQ(fnmatch::match("potato/normal\\go", "p?tat?\\no?mal/go", {foption::MatchAnySeparator}), true);
    EXPECT_EQ(fnmatch::match("potato/normal\\godude", "po*o\\n*l/go*", {foption::MatchAnySeparator}), true);
}