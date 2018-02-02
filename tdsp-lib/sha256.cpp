#include <array>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "sha256.h"

static std::uint32_t RotateRight(std::uint32_t x, size_t amount) {
    amount %= 32;
    if (amount == 0)
        return x;
    return (x >> amount) | (x << (32 - amount));
}

static size_t AlignUp(size_t value, size_t alignment) {
    return value + (alignment - value % alignment) % alignment;
}

static uint32_t GetBigEndianValue(const unsigned char* data) {
    return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}

static void ToBigEndianBytes(uint32_t value, unsigned char* data) {
    data[0] = value >> 24;
    data[1] = value >> 16;
    data[2] = value >> 8;
    data[3] = value >> 0;
}

std::array<unsigned char, 32> Sha256(const unsigned char* data, const size_t original_data_size) {
    static const std::array<std::uint32_t, 64> k {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };

    std::array<std::uint32_t, 8> hash {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19,
    };

    constexpr size_t chunk_size = 64;

    size_t remaining_data_size = original_data_size;
    size_t remaining_message_size = AlignUp(original_data_size + 1 + 8, chunk_size);

    for (; remaining_message_size != 0; remaining_data_size -= chunk_size, remaining_message_size -= chunk_size, data += chunk_size) {
        std::array<std::uint32_t, 64> w{};

        const size_t to_copy = std::min(chunk_size, remaining_data_size);
        std::memcpy(w.data(), data, to_copy);
        reinterpret_cast<unsigned char*>(w.data())[to_copy] = 0x80;
        for (std::uint32_t& x : w) {
            std::array<unsigned char, 4> y;
            std::memcpy(y.data(), &x, sizeof(std::uint32_t));
            x = (static_cast<std::uint32_t>(y[0]) << 24) | (static_cast<std::uint32_t>(y[1]) << 16) | (static_cast<std::uint32_t>(y[2]) << 8) | static_cast<std::uint32_t>(y[3]);
        }
        if (remaining_message_size == chunk_size) {
            w[chunk_size / 4 - 1] = original_data_size * 8;
            w[chunk_size / 4 - 2] = (original_data_size * 8) >> 32;
        }

        for (size_t i = 16; i < 64; i++) {
            const uint32_t s0 = RotateRight(w[i - 15], 7) ^ RotateRight(w[i - 15], 18) ^ (w[i - 15] >> 3);
            const uint32_t s1 = RotateRight(w[i - 2], 17) ^ RotateRight(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        std::uint32_t a = hash[0];
        std::uint32_t b = hash[1];
        std::uint32_t c = hash[2];
        std::uint32_t d = hash[3];
        std::uint32_t e = hash[4];
        std::uint32_t f = hash[5];
        std::uint32_t g = hash[6];
        std::uint32_t h = hash[7];

        for (size_t i = 0; i < 64; i++) {
            const std::uint32_t S1 = RotateRight(e, 6) ^ RotateRight(e, 11) ^ RotateRight(e, 25);
            const std::uint32_t ch = (e & f) ^ ((~e) & g);
            const std::uint32_t temp1 = h + S1 + ch + k[i] + w[i];
            const std::uint32_t S0 = RotateRight(a, 2) ^ RotateRight(a, 13) ^ RotateRight(a, 22);
            const std::uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            const std::uint32_t temp2 = S0 + maj;
     
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }

    std::array<unsigned char, 32> result;
    ToBigEndianBytes(hash[0], result.data() + 0 * 4);
    ToBigEndianBytes(hash[1], result.data() + 1 * 4);
    ToBigEndianBytes(hash[2], result.data() + 2 * 4);
    ToBigEndianBytes(hash[3], result.data() + 3 * 4);
    ToBigEndianBytes(hash[4], result.data() + 4 * 4);
    ToBigEndianBytes(hash[5], result.data() + 5 * 4);
    ToBigEndianBytes(hash[6], result.data() + 6 * 4);
    ToBigEndianBytes(hash[7], result.data() + 7 * 4);
    return result;
}
