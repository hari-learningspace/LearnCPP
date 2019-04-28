#include "mock_turtle.h"
#include "painter.h"

#include "gtest/gtest.h"

using ::testing::AtLeast;

TEST(PainterTest, CanDrawSomething)
{
        MockTurtle mturtle;
        EXPECT_CALL(mturtle, PenDown());
        Painter painter(&mturtle);

        EXPECT_TRUE(painter.DrawCircle(0,0,10));
}