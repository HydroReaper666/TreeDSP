#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <vector>

std::array<unsigned char, 32> Sha256(const unsigned char* data, const size_t size);

template <typename T>
inline std::array<unsigned char, 32> Sha256(const std::vector<T>& v) {
    return Sha256(reinterpret_cast<const unsigned char*>(v.data()), v.size() * sizeof(T));
}

inline std::array<unsigned char, 32> Sha256(const std::string& v) {
    return Sha256(reinterpret_cast<const unsigned char*>(v.data()), v.size() * sizeof(unsigned char));
}
