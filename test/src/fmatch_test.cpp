#include <gtest/gtest.h>
#include "fmatch.hpp"

using namespace std;

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
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "potato/normal/**"), true);
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "potato/normal/*"), false);
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "po*o/n*al/**"), true);
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "po*o/n*al/go**"), true);
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "po*o/n*al/go*"), false);
    EXPECT_EQ(fmatch::match("potato/n", "po*o/**"), true);
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello", "po*o/n*a**"), true);
}

TEST(match, double_asterisk_between)
{
    EXPECT_EQ(fmatch::match("hello/world/neighbour", "hell*bour"), false);
    EXPECT_EQ(fmatch::match("hello/world/neighbour", "hell**bour"), true);
}

TEST(match, double_asterisk_between_directories)
{
    EXPECT_EQ(fmatch::match("hello/main.cpp", "hello/**/main.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/world/main.cpp", "hello/**/main.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/world/neighbour/main.cpp", "hello/**/main.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/world/neighbourmain.cpp", "hello/**/main.cpp"), false);
    EXPECT_EQ(fmatch::match("hello/world/neighbourmain.cpp", "hello/**/*.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/world/main.cpp", "hello/wo**/main.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/world/main.cpp/jim", "hello/**/main.cpp"), false);
    EXPECT_EQ(fmatch::match("hello/world/neighbour/min.js", "hello/**/*.js"), true);
    EXPECT_EQ(fmatch::match("hello/world/neighbour/min.js", "hello/**/*.cpp"), false);
    EXPECT_EQ(fmatch::match("hello/main.cpp", "hello/**/*.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/world/main.cpp", "hello/**/*.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/world/main.cpp", "hello/**/*.cpo"), false);
    EXPECT_EQ(fmatch::match("hello/world/main.cpp", "hello/**/*.*"), true);
    EXPECT_EQ(fmatch::match("hello/gago/gogo/world/main.cpp", "hello/**/w*d/*.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/gago/gogo/worl/main.cpp", "hello/**/w*d/*.cpp"), false);
    EXPECT_EQ(fmatch::match("hello/gago/gogo/world/main.cpp", "hello/g**/w*d/*.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/gago/gogo/world/main.cpp", "hello/ga*/w*d/*.cpp"), false);
    EXPECT_EQ(fmatch::match("hello/world/!project!", "h**/!*!"), true);
    EXPECT_EQ(fmatch::match("eello/world/!project!", "h**/!*!"), false);
    EXPECT_EQ(fmatch::match("!project!", "!*!"), true);
}

TEST(match, double_asterisk_at_start)
{
    EXPECT_EQ(fmatch::match("hello/world/main.cpp", "**"), true);
    EXPECT_EQ(fmatch::match("hello", "**"), true);
    EXPECT_EQ(fmatch::match("hello", "**/hello"), true);
    EXPECT_EQ(fmatch::match("!hello!.py", "**/*!*!.py"), true);
    EXPECT_EQ(fmatch::match("!hello!g.py", "**/*!*!.py"), false);
    EXPECT_EQ(fmatch::match("!hello!g.py", "**/*!*!*.py"), true);
    EXPECT_EQ(fmatch::match("hello/!project!", "**/!*!"), true);
    EXPECT_EQ(fmatch::match("hello/world/!project!", "**/!*!"), true);
    EXPECT_EQ(fmatch::match("!project!", "**/!*!"), true);
    EXPECT_EQ(fmatch::match("hello/world/!project!", "**/!*!"), true);
    EXPECT_EQ(fmatch::match("!project!", "**/*!*!*"), true);
    EXPECT_EQ(fmatch::match("hello/world/!project!", "**/*!*!*"), true);
    EXPECT_EQ(fmatch::match("!project!", "**/*!*!*"), true);
    EXPECT_EQ(fmatch::match("bobo!project!amp", "**/*!*!*"), true);
    EXPECT_EQ(fmatch::match("hello/world/bobo!project!amp", "**/*!*!*"), true);
    EXPECT_EQ(fmatch::match("hello/!world!/bobo!project!amp", "**/*!*!*"), true);
    EXPECT_EQ(fmatch::match("!project", "**/*!*!*"), false);
}

TEST(match, double_asterisk_at_end)
{
    EXPECT_EQ(fmatch::match("!project!", "!*!/**"), false);
    EXPECT_EQ(fmatch::match("!project!", "!*!/**n"), false);
    EXPECT_EQ(fmatch::match("!project!", "!*!/m**"), false);
    EXPECT_EQ(fmatch::match("!project!", "!*!*/**"), false);
    EXPECT_EQ(fmatch::match("!project!", "!*!m/**"), false);
    EXPECT_EQ(fmatch::match("!project!mo", "!*!/m**"), false);
    EXPECT_EQ(fmatch::match("!project!/gin", "!*!*/**"), false);

    EXPECT_EQ(fmatch::match("!project!/good", "!*!/**"), true);
    EXPECT_EQ(fmatch::match("!project!/mo", "!*!/m**"), true);
    EXPECT_EQ(fmatch::match("!project!m/gin", "!*!m/**"), true);
}

TEST(match, asterisk_skipping_separator)
{
    EXPECT_EQ(fmatch::match("potato/normal/godude", "potato/no*dude"), false);
    EXPECT_EQ(fmatch::match("potato/normal/godude", "pot*dude"), false);
}

TEST(match, end_separators)
{
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello//", "potato/normal/**/"), true);
    EXPECT_EQ(fmatch::match("potato/normal/godude/hello/", "potato/normal/*/"), false);
}

TEST(match, any)
{
    EXPECT_EQ(fmatch::match("potato/normal/go", "p?tat?/no?mal/go"), true);
}

TEST(match, complex_pattern)
{
    EXPECT_EQ(fmatch::match("hello/gago/gogo/world/main.cpp", "hello/g**d/*.cpp"), true);
    EXPECT_EQ(fmatch::match("hello/gago/gogo/world/main.cpp", "hello/g**d/*.???"), true);
    EXPECT_EQ(fmatch::match("hello/gago/gogo/world/main.cp", "hello/g**d/*.???"), false);
}

TEST(match, edge_case)
{
    EXPECT_EQ(fmatch::match("potato", "potato/more/*"), false);
    EXPECT_EQ(fmatch::match("potato", "pot"), false);
    EXPECT_EQ(fmatch::match("potato", "potato/**"), false);
}

TEST(match, root_path)
{
    EXPECT_EQ(fmatch::match("D:/hello/world", "D:/**"), true);
    EXPECT_EQ(fmatch::match("D:/hello/world", "D:/*"), false);
}