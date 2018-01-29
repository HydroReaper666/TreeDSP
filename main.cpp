#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>

#include "asm_lexer.h"
#include "asm_parse.h"
#include "instruction_table_lexer.h"

const std::string instruction_table = 
#include "instruction_table.inc"
;

std::vector<InstructionParser> BuildParserTable() {
    std::vector<InstructionParser> table;

    std::istringstream stream{instruction_table};
    InstructionTableLexer lexer{stream};

    while (true) {
        while (lexer.PeekToken().type == InstructionTableToken::END_OF_LINE && lexer.PeekToken().type != InstructionTableToken::END_OF_FILE)
            lexer.NextToken();

        if (lexer.PeekToken().type == InstructionTableToken::END_OF_FILE)
            break;

        assert(lexer.PeekToken().type == InstructionTableToken::HEX);
        const std::uint16_t instruction_bits = std::strtol(lexer.NextToken().payload.c_str(), nullptr, 16);

        InstructionPartList part_list;

        while (lexer.PeekToken().type != InstructionTableToken::END_OF_LINE) {
            auto token = lexer.NextToken();
            assert(token.type == InstructionTableToken::IDENTIFIER);

            bool invert = false;

            const auto parse_at_bit_pos = [&]() -> size_t {
                assert(lexer.NextToken().type == InstructionTableToken::AT);
                if (lexer.PeekToken().payload == "not")
                    invert = true;
                assert(lexer.PeekToken().type == InstructionTableToken::NUMBER);
                return std::strtol(lexer.NextToken().payload.c_str(), nullptr, 10);
            };

            if (token.payload == "Implied") {
                // Ignore
            } else if (token.payload == "NoReverse") {
                assert(lexer.NextToken().payload == ",");
            } else if (token.payload == "||") {
                part_list.emplace_back(std::make_shared<TokenTypePart<AsmToken::DoublePipe>>());
            } else if (token.payload == "_") {
                part_list.emplace_back(std::make_shared<TokenTypePart<AsmToken::Colon>>());
            } else if (token.payload == "MemSp") {
                part_list.emplace_back(std::make_shared<MemSp>());
            } else if (token.payload == "MemRn") {
                part_list.emplace_back(std::make_shared<MemRn>(parse_at_bit_pos()));
            } else if (token.payload == "ProgMemRn") {
                part_list.emplace_back(std::make_shared<ProgMemRn>(parse_at_bit_pos()));
            } else if (token.payload == "ProgMemAxl") {
                part_list.emplace_back(std::make_shared<ProgMemAxl>(parse_at_bit_pos()));
            } else if (token.payload == "ProgMemAx") {
                part_list.emplace_back(std::make_shared<ProgMemAx>(parse_at_bit_pos()));
            } else if (token.payload == "MemImm8") {
                part_list.emplace_back(std::make_shared<MemImm8>(parse_at_bit_pos()));
            } else if (token.payload == "MemImm16") {
                part_list.emplace_back(std::make_shared<MemImm16>(parse_at_bit_pos()));
            } else if (token.payload == "MemR7Imm7s") {
                part_list.emplace_back(std::make_shared<MemR7Imm7s>(parse_at_bit_pos()));
            } else if (token.payload == "MemR7Imm16") {
                part_list.emplace_back(std::make_shared<MemR7Imm16>(parse_at_bit_pos()));
            } else if (token.payload == "Imm8u") {
                part_list.emplace_back(std::make_shared<Imm8u>(parse_at_bit_pos()));
            } else if (token.payload == "Imm16") {
                part_list.emplace_back(std::make_shared<Imm16>(parse_at_bit_pos()));
            } else if (token.payload == "stepZIDS") {
                part_list.emplace_back(std::make_shared<stepZIDS>(parse_at_bit_pos()));
            } else if (token.payload == "Rn") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Rn, parse_at_bit_pos()));
            } else if (token.payload == "Ax") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Ax, parse_at_bit_pos()));
            } else if (token.payload == "Axl") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Axl, parse_at_bit_pos()));
            } else if (token.payload == "Axh") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Axh, parse_at_bit_pos()));
            } else if (token.payload == "Bx") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Bx, parse_at_bit_pos()));
            } else if (token.payload == "Bxl") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Bxl, parse_at_bit_pos()));
            } else if (token.payload == "Bxh") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Bxh, parse_at_bit_pos()));
            } else if (token.payload == "Ab") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Ab, parse_at_bit_pos()));
            } else if (token.payload == "Abl") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Abl, parse_at_bit_pos()));
            } else if (token.payload == "Abh") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Abh, parse_at_bit_pos()));
            } else if (token.payload == "Abe") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Abe, parse_at_bit_pos()));
            } else if (token.payload == "Px") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Px, parse_at_bit_pos()));
            } else if (token.payload == "Ablh") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Ablh, parse_at_bit_pos()));
            } else if (token.payload == "Cond") {
                part_list.emplace_back(std::make_shared<SetOfIdentifierPart>(set_Cond, parse_at_bit_pos()));
            } else {
                part_list.emplace_back(std::make_shared<SingleIdentifierPart>(token.payload));
            }

            if (invert) {
                auto part = part_list.back();
                part_list.pop_back();
                part_list.emplace_back(std::make_shared<Not>(part));
            }
        }

        table.emplace_back(InstructionParser{instruction_bits, part_list});
    }

    return table;
}

void test_a() {
    std::istringstream stream{"mov [0x100], a1"};
    AsmLexer lexer{stream};

    auto line = GetLine(lexer);

    for (const auto& token : *line) {
        // printf("%s\n", AsmToken::ToString(token).c_str());
    }

    InstructionParser parser {
        0xD4FB,
        InstructionPartList {
            std::make_shared<SingleIdentifierPart>("mov"),
            std::make_shared<MemImm16>(16),
            std::make_shared<SingleIdentifierPart>(","),
            std::make_shared<SetOfIdentifierPart>(set_Ax, 8),
        }
    };

    auto result = parser.TryParse(*line);

    assert(result);
    assert(result->size() == 2);
    assert(result->at(0) == 0xd5fb);
    assert(result->at(1) == 0x0100);
}

int main() {
    test_a();

    auto table = BuildParserTable();

    AsmLexer lexer{std::cin};

    auto line = GetLine(lexer);

    /*
    printf("\nTokens:\n");
    for (const auto& token : *line) {
        printf("%s\n", AsmToken::ToString(token).c_str());
    }
    */

    printf("\nHex:\n");
    for (auto& parser : table) {
        if (auto result = parser.TryParse(*line)) {
            for (std::uint16_t v : *result) {
                printf("%04x\n", v);
            }
            break;
        }
    }

    return 0;
}
