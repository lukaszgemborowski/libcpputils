#ifndef TYPE_READER_H
#define TYPE_READER_H

#include <istream>
#include <tuple>

namespace cpputils
{

template<typename T, int S>
class array_reader {
public:
    void read_from_stream(std::istream &stream) {
        stream.read((char *)&buffer[0], sizeof(T) * S);
    }

    int size() const {
        return S * sizeof(T);
    }

    T value(int index) const {
        return buffer[index];
    }

private:
    T buffer[S];
};

template<typename T>
class value_reader : public array_reader<T, 1> {
public:
    T value() const {
        return array_reader<T, 1>::value(0);
    }
};

template<typename T, typename Allocator = std::allocator<T>>
class vector_reader {
public:
    vector_reader(int size) : buffer(size) {}

    void read_from_stream(std::istream &stream) {
        stream.read((char *)buffer.data(), sizeof(T) * buffer.size());
    }

    T value(int index) const {
        return buffer[index];
    }

    int size() const {
        return sizeof(T) * buffer.size();
    }

private:
    std::vector<T, Allocator> buffer;
};

/* forward declarations needed by calculate_size(std::tuple<Tp...> &t) */
template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), int>::type
block_size(std::tuple<Tp...>&);

template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I < sizeof...(Tp), int>::type
block_size(std::tuple<Tp...>& t);

/* sizeof POD type */
template<typename T>
typename std::enable_if<std::is_pod<T>::value, int>::type
calculate_size(T &) {
    return sizeof(T);
}

/* sizeof non-pod type, require to implement size method */
template<typename T>
typename std::enable_if<!std::is_pod<T>::value, int>::type
calculate_size(T &t) {
    return t.size();
}

/* recursive sizeof a tuple */
template<typename... Tp>
int calculate_size(std::tuple<Tp...> &t) {
    return block_size(t);
}

template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), int>::type
block_size(std::tuple<Tp...>&) { return 0; }

template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I < sizeof...(Tp), int>::type
block_size(std::tuple<Tp...>& t) {
    return calculate_size(std::get<I>(t)) + block_size<I + 1, Tp...>(t);
}

}

#endif // TYPE_READER_H
