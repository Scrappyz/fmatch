#include <gtest/gtest.h>
#include "fnmatch.hpp"

using namespace std;

TEST(match, matching)
{
    EXPECT_EQ(fnmatch::match("potato/normal/go", "potato/normal/go"), true);
    EXPECT_EQ(fnmatch::match("potato/normal/go", "potato/normal/god"), false);
    EXPECT_EQ(fnmatch::match("potato/normal/god", "potato/normal/go"), false);
    EXPECT_EQ(fnmatch::match("potato/nl/god", "potato/normal/go"), false);
}

TEST(match, asterisk)
{
    EXPECT_EQ(fnmatch::match("potato/n*l/go", "potato/normal/go"), true);
    EXPECT_EQ(fnmatch::match("po*o/normal/go", "potato/normal/go"), true);
    EXPECT_EQ(fnmatch::match("my_project/*.cpp", "my_project/main.cpp"), true);
}

TEST(match, asterisk_end)
{
    EXPECT_EQ(fnmatch::match("potato/normal/go*", "potato/normal/godude"), true);
}

TEST(match, multiple_asterisk)
{
    EXPECT_EQ(fnmatch::match("po*o/n*l/go*", "potato/normal/godude"), true);
    EXPECT_EQ(fnmatch::match("my_project/*.*", "my_project/main.cpp"), true);
    EXPECT_EQ(fnmatch::match("my_project/*.*", "my_project/test.txt"), true);
}

TEST(match, asterisk_subdirectories)
{
    EXPECT_EQ(fnmatch::match("po*o/n*l/go*", "potato/normal/godude/hello"), true);
    EXPECT_EQ(fnmatch::match("po*o/n*l/go*/", "potato/normal/godude/hello"), false);
}

TEST(match, asterisk_current_directory)
{
    EXPECT_EQ(fnmatch::match("po*o/n*l/*/", "potato/normal/godude/hello"), false);
    EXPECT_EQ(fnmatch::match("po*o/n*l/*/", "potato/normal/godude/"), true);
}