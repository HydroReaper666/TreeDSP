#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>

#include "asm_lexer.h"
#include "asm_parse.h"
#include "instruction_table_lexer.h"

int main() {
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
