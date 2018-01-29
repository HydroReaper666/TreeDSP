#pragma once

#include <climits>
#include <cstddef>

template<typename T>
constexpr size_t BitSize() {
    return sizeof(T) * CHAR_BIT;
}

template <typename T>
inline bool IsPowerOf2(T x) {
    return x && !(x & (x - 1));
}

template <typename T>
inline T Log2(T x) {
    size_t result = 0;
    T test = 1;
    while (test < x) {
        test *= 2;
        result++;
    }
    return result;
}

template <typename T>
inline T NextPowerOf2(T x) {
    T result = 1;
    while (result < x) {
        result *= 2;
    }
    return result;
}

template <typename T>
inline T Ones(size_t count) {
    assert(count <= BitSize<T>() && "count larger than bitsize of T");
    if (count == BitSize<T>())
        return ~static_cast<T>(0);
    return ~(~static_cast<T>(0) << count);
}
