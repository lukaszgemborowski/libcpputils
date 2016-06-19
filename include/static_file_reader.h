#ifndef STATICFILEREADER_H
#define STATICFILEREADER_H

#include <istream>
#include <type_traits>
#include <tuple>
#include <utility>

namespace cpputils
{

template<typename S>
class static_file_reader {
public:
    static_file_reader(S &&stream) :
        stream(std::move(stream))
    {}

    template<std::size_t I = 0, typename... Tp>
    typename std::enable_if<I == sizeof...(Tp), void>::type
    read(std::tuple<Tp...>&) {}

    template<std::size_t I = 0, typename... Tp>
    typename std::enable_if<I < sizeof...(Tp), void>::type
    read(std::tuple<Tp...>& t) {
        extract(std::get<I>(t));
        read<I + 1, Tp...>(t);
    }

    template<typename... Tp> void extract(std::tuple<Tp...>& t) {
        read(t);
    }

    template<typename T> void extract(T &t) {
        t.read_from_stream(stream);
    }

    S&& get_stream() {
        return std::move(stream);
    }

private:
    S stream;
};

}

#endif // STATICFILEREADER_H
