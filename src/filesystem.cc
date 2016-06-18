#include <filesystem.h>
#include <experimental/filesystem>

namespace cpputils
{

std::string file_extension(const std::string &filename)
{
	namespace fs = std::experimental::filesystem;
	return fs::path(filename).extension().string().substr(1);
}

}
