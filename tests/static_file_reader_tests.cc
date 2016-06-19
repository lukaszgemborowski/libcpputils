#include "gtest/gtest.h"
#include "static_file_reader.h"
#include "type_reader.h"
#include <sstream>

using namespace cpputils;

TEST(static_file_reader_tests, read_integral_tuple)
{
	int input[] = {1, 2, 3};
	std::stringstream stream;
	stream.write((char *)&input[0], sizeof (input));

	static_file_reader<std::stringstream> reader(std::move(stream));

	std::tuple<int, int, int> buffer;

	reader.read(buffer);

	ASSERT_EQ(1, std::get<0>(buffer));
	ASSERT_EQ(2, std::get<1>(buffer));
	ASSERT_EQ(3, std::get<2>(buffer));
}

TEST(static_file_reader_tests, read_arrays)
{
	int input[] = {1, 2, 3};
	std::stringstream stream;
	stream.write((char *)&input[0], sizeof (input));

	static_file_reader<std::stringstream> reader(std::move(stream));

	std::tuple<int [3]> buffer;

	reader.read(buffer);

	ASSERT_EQ(1, std::get<0>(buffer)[0]);
	ASSERT_EQ(2, std::get<0>(buffer)[1]);
	ASSERT_EQ(3, std::get<0>(buffer)[2]);
}

TEST(static_file_reader_tests, read_real_numbers)
{
	float input[] = {1.2f, 3.4f, 5.6f};
	std::stringstream stream;
	stream.write((char *)&input[0], sizeof (input));

	static_file_reader<std::stringstream> reader(std::move(stream));

	std::tuple<float[3]> buffer;

	reader.read(buffer);

	ASSERT_EQ(1.2f, std::get<0>(buffer)[0]);
	ASSERT_EQ(3.4f, std::get<0>(buffer)[1]);
	ASSERT_EQ(5.6f, std::get<0>(buffer)[2]);
}

TEST(static_file_reader_tests, read_simple_tuple)
{
	// prepare a stream of 3 ints
	int input[] = {1, 2, 3};
	std::stringstream stream;
	stream.write((char *)&input[0], sizeof (input));

	// now read array of three ints from the stream
	static_file_reader<std::stringstream> reader(std::move(stream));

	std::tuple<
		array_reader<int, 2>,
		array_reader<int, 1>> buffer;

	reader.read(buffer);

	// check
	ASSERT_EQ(1, std::get<0>(buffer).value(0));
	ASSERT_EQ(2, std::get<0>(buffer).value(1));
	ASSERT_EQ(3, std::get<1>(buffer).value(0));
}

TEST(static_file_reader_tests, multi_tuple_definition)
{
	// prepare a stream of 3 ints
	int input[] = {1, 2, 3};
	std::stringstream stream;
	stream.write((char *)&input[0], sizeof (input));

	// now read array of three ints from the stream
	static_file_reader<std::stringstream> reader(std::move(stream));

	typedef std::tuple<array_reader<int, 2>> first;
	typedef std::tuple<array_reader<int, 1>> second;

	std::tuple<first, second> buffer;

	reader.read(buffer);

	// check
	first f = std::get<0>(buffer);
	second s = std::get<1>(buffer);

	ASSERT_EQ(1, std::get<0>(f).value(0));
	ASSERT_EQ(2, std::get<0>(f).value(1));
	ASSERT_EQ(3, std::get<0>(s).value(0));
}
