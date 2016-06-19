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

    S&& get_stream() {
        return std::move(stream);
    }

    bool eof() {
        return stream.eof();
    }

private:
    // extract a sub-tuple
    template<typename... Tp> void extract(std::tuple<Tp...>& t) {
        read(t);
    }

    template<std::size_t I = 0, typename T, size_t N>
    typename std::enable_if<I == N, void>::type
    extract_array(T (&)[N]) {}

    template<std::size_t I = 0, typename T, size_t N>
    typename std::enable_if<I < N, void>::type
    extract_array(T (&t)[N]) {
        extract(t[I]);
        extract_array<I + 1, T, N>(t);
    }

    // extract array
    template<typename T, size_t N> void
    extract(T (&t)[N]) {
        extract_array(t);
    }

    // extract integral type
    template<typename T>
    typename std::enable_if<std::is_pod<T>::value, void>::type
    extract(T &t) {
        stream.read((char *)&t, sizeof(T));
    }

    // extract custom type
    template<typename T>
    typename std::enable_if<!std::is_pod<T>::value, void>::type
    extract(T &t) {
        t.read_from_stream(stream);
    }

private:
    S stream;
};

}

#endif // STATICFILEREADER_H
