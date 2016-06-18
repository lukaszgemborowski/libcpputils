#ifndef TYPE_READER_H
#define TYPE_READER_H

#include <fstream>

namespace reader
{

template<typename T, int S>
class array_reader {
public:
    void read_from_stream(std::ifstream &stream) {
        stream.read((char *)&buffer[0], sizeof(T) * S);
    }

    int size() const {
        return S;
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

}

#endif // TYPE_READER_H

