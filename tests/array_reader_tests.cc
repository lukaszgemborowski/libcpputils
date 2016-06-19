#include "gtest/gtest.h"
#include "type_reader.h"
#include <sstream>

using namespace cpputils;

TEST(array_reader_tests, can_be_created)
{
	array_reader<int, 1>();
}

TEST(array_reader_tests, read_int_array)
{
	/* prepare a stream of 3 ints */
	int input[] = {1, 2, 3};
	std::stringstream stream;
	stream.write((char *)&input[0], sizeof (input));

	/* now read array of three ints from the stream */
	array_reader<int, 3> int_reader;
	int_reader.read_from_stream(stream);

	/* check the result */
	ASSERT_EQ(1, int_reader.value(0));
	ASSERT_EQ(2, int_reader.value(1));
	ASSERT_EQ(3, int_reader.value(2));
}

TEST(reader_tests, vector_reader_test)
{
	/* prepare a stream of 3 ints */
	int input[] = {1, 2, 3};
	std::stringstream stream;
	stream.write((char *)&input[0], sizeof (input));

	vector_reader<int> reader(3);
	reader.read_from_stream(stream);

	/* check the result */
	ASSERT_EQ(1, reader.value(0));
	ASSERT_EQ(2, reader.value(1));
	ASSERT_EQ(3, reader.value(2));
}
