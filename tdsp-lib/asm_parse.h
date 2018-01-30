#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "part_parse_result.h"

class AsmInstructionPart;

using InstructionPartList = std::vector<std::shared_ptr<AsmInstructionPart>>;

std::optional<PartParseResult> ProcessPartList(TokenList tl, const InstructionPartList& part_list);

class InstructionParser {
public:
    InstructionParser(std::uint16_t instruction_bits, InstructionPartList part_list);

    std::optional<std::vector<std::uint16_t>> TryParse(const TokenList& tl) const;

private:
    std::uint16_t instruction_bits;
    InstructionPartList part_list;
};

std::vector<InstructionParser> BuildParserTable();
