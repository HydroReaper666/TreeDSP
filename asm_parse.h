#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "asm_instruction_part.h"

using InstructionPartList = std::vector<std::shared_ptr<AsmInstructionPart>>;

struct SetBits {
    std::uint32_t bits = 0;
    std::uint32_t mask = 0;
};

inline std::optional<SetBits> ProcessPartList(TokenList tl, const InstructionPartList& part_list) {
    std::vector<SetBits> results;

    for (auto& part : part_list) {
        if (auto result = part->Parse(tl)) {
            results.emplace_back(SetBits{*result, part->GetMask()});
        } else {
            return std::nullopt;
        }
    }

    if (!tl.empty())
        return std::nullopt;

    std::uint32_t bits = 0;
    std::uint32_t mask = 0;
    for (auto& result : results) {
        assert((result.bits & result.mask) == result.bits);
        std::uint32_t overlapping_mask = result.mask & mask; 
        if ((result.bits & overlapping_mask) != (bits & overlapping_mask))
            return std::nullopt;
        bits |= result.bits;
        mask |= result.mask;
    }

    return SetBits{bits, mask};
}

class InstructionParser {
public:
    InstructionParser(std::uint16_t instruction_bits, InstructionPartList part_list) : instruction_bits(instruction_bits), part_list(part_list) {}

    std::optional<std::vector<std::uint16_t>> TryParse(const TokenList& tl) const {
        auto set_bits = ProcessPartList(tl, part_list);
        if (!set_bits)
            return std::nullopt;

        std::vector<std::uint16_t> result;
        result.emplace_back(static_cast<std::uint16_t>(set_bits->bits) | instruction_bits);
        if (set_bits->mask & 0xFFFF0000) {
            result.emplace_back(static_cast<std::uint16_t>(set_bits->bits >> 16));
        }
        return result;
    }

private:
    std::uint16_t instruction_bits;
    InstructionPartList part_list;
};
