#include "instruction_table_lexer.h"

InstructionTableLexer::InstructionTableLexer(std::istream& stream) : s(stream) {}

InstructionTableToken InstructionTableLexer::PeekToken() {
    if (!current_token)
        current_token = NextToken();
    return *current_token;
}

InstructionTableToken InstructionTableLexer::NextToken() {
    if (current_token) {
        return *std::exchange(current_token, std::nullopt);
    }

    SkipWhitespace();

    if (s.peek() == '\n') {
        start_of_line = true;
        s.get();
        return {InstructionTableToken::END_OF_LINE, "EOL"};
    }
    if (s.peek() == EOF) {
        return {InstructionTableToken::END_OF_FILE, "EOF"};
    }
    if (start_of_line) {
        start_of_line = false;
        return LexHex();
    }
    if ((s.peek() >= 'a' && s.peek() <= 'z') || (s.peek() >= 'A' && s.peek() <= 'Z')) {
        return LexIdentifier();
    }
    if (s.peek() >= '0' && s.peek() <= '9') {
        return LexNumber();
    }
    if (s.peek() == '@') {
        s.get();
        return {InstructionTableToken::AT, "@"};
    }
    if (s.peek() == ',') {
        s.get();
        return {InstructionTableToken::IDENTIFIER, ","};
    }
    if (s.peek() == '_') {
        s.get();
        return {InstructionTableToken::IDENTIFIER, "_"};
    }
    if (s.peek() == '|') {
        s.get();
        if (s.get() == '|')
            return {InstructionTableToken::IDENTIFIER, "||"};
        return {InstructionTableToken::ERROR, ""};
    }

    return {InstructionTableToken::ERROR, ""};
}

void InstructionTableLexer::SkipWhitespace() {
    while (s.peek() == ' ' || s.peek() == '\t' || s.peek() == '\r') {
        s.get();
    }

    // Comment til end of line
    if (s.peek() == ';') {
        while (s.peek() != '\n') {
            s.get();
        }
    }
}

InstructionTableToken InstructionTableLexer::LexHex() {
    InstructionTableToken result;
    result.type = InstructionTableToken::HEX;

    const auto is_hex_digit = [](int ch) {
        return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z');
    };

    for (size_t i = 0; i < 4; i++) {
        int ch = s.get();
        if (!is_hex_digit(ch))
            return {InstructionTableToken::ERROR, ""};
        result.payload += (char)ch;
    }

    if (s.get() != 'h')
        return {InstructionTableToken::ERROR, ""};

    return result;
}

InstructionTableToken InstructionTableLexer::LexNumber() {
    InstructionTableToken result;
    result.type = InstructionTableToken::NUMBER;

    while (s.peek() >= '0' && s.peek() <= '9') {
        int ch = s.get();
        result.payload += (char)ch;
    }

    return result;
}

InstructionTableToken InstructionTableLexer::LexIdentifier() {
    InstructionTableToken result;
    result.type = InstructionTableToken::IDENTIFIER;

    while ((s.peek() >= '0' && s.peek() <= '9') || (s.peek() >= 'a' && s.peek() <= 'z') || (s.peek() >= 'A' && s.peek() <= 'Z')) {
        int ch = s.get();
        result.payload += (char)ch;
    }

    return result;
}
