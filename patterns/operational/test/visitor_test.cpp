#include <gtest/gtest.h>
#include <string>
#include "visitor.hpp"

TEST(VisitorTest, Constructor)
{
	testing::internal::CaptureStdout();
	Visitor v;
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_EQ(output, "constructing\n");
}
