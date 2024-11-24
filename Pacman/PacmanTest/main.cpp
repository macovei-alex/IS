#include <gtest/gtest.h>

#include "PacmanTests.cpp"
#include "MazeTests.cpp"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
