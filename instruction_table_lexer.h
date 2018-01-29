#pragma once

#include <istream>
#include <string>
#include <optional>

struct InstructionTableToken {
    enum {
        HEX,
        IDENTIFIER,
        AT,
        NUMBER,
        END_OF_LINE,
        END_OF_FILE,
        ERROR,
    } type;

    std::string payload;
};

struct InstructionTableLexer {
public:
    explicit InstructionTableLexer(std::istream& stream);

    InstructionTableToken PeekToken();
    InstructionTableToken NextToken();

private:
    void SkipWhitespace();

    InstructionTableToken LexHex();
    InstructionTableToken LexIdentifier();
    InstructionTableToken LexNumber();

    bool start_of_line = true;
    std::istream& s;
    std::optional<InstructionTableToken> current_token;
};
