#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>

#include "asm_parse.h"
#include "instruction_table_lexer.h"

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
            std::make_shared<TokenTypePart<AsmToken::Comma>>(),
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

    printf("\nTokens:\n");
    for (const auto& token : *line) {
        printf("%s\n", AsmToken::ToString(token).c_str());
    }

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
