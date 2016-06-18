#ifndef STATICFILEREADER_H
#define STATICFILEREADER_H

#include <istream>
#include <type_traits>
#include <tuple>

class static_file_reader {
public:
    static_file_reader(std::istream &&stream) :
        stream(std::move(stream))
    {}

    template<std::size_t I = 0, typename... Tp>
    typename std::enable_if<I == sizeof...(Tp), void>::type
    read(std::tuple<Tp...>&) {}

    template<std::size_t I = 0, typename... Tp>
    typename std::enable_if<I < sizeof...(Tp), void>::type
    read(std::tuple<Tp...>& t) {
        std::get<I>(t).read_from_stream(stream);
        read<I + 1, Tp...>(t);
    }

    std::istream&& get_stream() {
        return std::move(stream);
    }

private:
    std::istream stream;
};

#endif // STATICFILEREADER_H
