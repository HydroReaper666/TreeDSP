#pragma once

#include <cstddef>
#include <cstdint>

struct PartLabelDependency {
    std::string label_name;
    size_t bit_count_beyond_16;
    size_t bit_position;
};

struct PartParseResult {
    ParseResult() = default;
    ParseResult(std::uint32_t bits, std::uint32_t mask) : bits(bits), mask(mask) {}
    ParseResult(std::uint32_t bits, std::uint32_t mask, std::optional<LabelDependency> label_dependency) : bits(bits), mask(mask), label_dependency(label_dependency) {}

    std::uint32_t bits = 0;
    std::uint32_t mask = 0;
    std::optional<LabelDependency> label_dependency;
};
