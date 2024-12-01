#include <gtest/gtest.h>

#include "PacmanTests.h"
#include "MazeTests.h"
#include "PathFinderTests.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
