#include "../src/Menu.hpp"
#include "../src/Snake.hpp"
#include "gtest/gtest.h"
#include <limits.h>

extern struct S {
    int x;
    int y;
} s[100];

namespace {

TEST(RotateHead, CorrectAngles)
{
    Sprite head;
    ASSERT_EQ(90, RotateHead(0, head));
    ASSERT_EQ(180, RotateHead(1, head));
    ASSERT_EQ(270, RotateHead(2, head));
    ASSERT_EQ(0, RotateHead(3, head));
}

TEST(RotateHead, UncorrectAngles)
{
    Sprite head;
    ASSERT_NE(-100, RotateHead(2, head));
    ASSERT_NE(450, RotateHead(1, head));
    ASSERT_NE(-100, RotateHead(3, head));
    ASSERT_NE(450, RotateHead(0, head));
    ASSERT_NE(-100, RotateHead(0, head));
    ASSERT_NE(450, RotateHead(2, head));
    ASSERT_NE(-100, RotateHead(1, head));
    ASSERT_NE(450, RotateHead(3, head));
}

TEST(SnakeCrush, Crush)
{
    s[0].x = -1;
    s[0].y = 0;
    ASSERT_EQ(0, SnakeCrush(s));
    s[0].x = 0;
    s[0].y = -1;
    ASSERT_EQ(0, SnakeCrush(s));
    s[0].x = 40;
    s[0].y = 0;
    ASSERT_EQ(0, SnakeCrush(s));
    s[0].x = 40;
    s[0].y = 1;
    ASSERT_EQ(0, SnakeCrush(s));
    s[0].x = 0;
    s[0].y = 40;
    ASSERT_EQ(0, SnakeCrush(s));
    s[0].x = 1;
    s[0].y = 40;
    ASSERT_EQ(0, SnakeCrush(s));
    s[0].x = -1;
    s[0].y = 40;
    ASSERT_EQ(0, SnakeCrush(s));
    s[0].x = 40;
    s[0].y = -1;
    ASSERT_EQ(0, SnakeCrush(s));
}

TEST(SnakeCrush, InField)
{
    s[0].x = 1;
    s[0].y = 1;
    ASSERT_EQ(1, SnakeCrush(s));
    s[0].x = 39;
    s[0].y = 1;
    ASSERT_EQ(1, SnakeCrush(s));
    s[0].x = 1;
    s[0].y = 39;
    ASSERT_EQ(1, SnakeCrush(s));
    s[0].x = 39;
    s[0].y = 39;
    ASSERT_EQ(1, SnakeCrush(s));
    s[0].x = 14;
    s[0].y = 28;
    ASSERT_EQ(1, SnakeCrush(s));
    s[0].x = 6;
    s[0].y = 10;
    ASSERT_EQ(1, SnakeCrush(s));
    s[0].x = 4;
    s[0].y = 34;
    ASSERT_EQ(1, SnakeCrush(s));
}
}
