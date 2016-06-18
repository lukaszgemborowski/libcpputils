#include "gtest/gtest.h"
#include "filesystem.h"

TEST(filesystem_tests, return_correct_extension)
{
	const std::string path = "some/path/to/file.test";

	ASSERT_EQ(std::string("test"), cpputils::file_extension(path));
}
