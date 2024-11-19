#include <iostream>
#include <gtest/gtest.h>


TEST(SampleTest, Test1)
{
	EXPECT_EQ(1 + 1, 2);
	EXPECT_TRUE(true);
	EXPECT_GT(5, 3);
}

TEST(SampleTest, Test2)
{
	EXPECT_EQ(1 + 1, 2);
	EXPECT_TRUE(false);
	EXPECT_GT(5, 3);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
