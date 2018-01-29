#include "asm_lexer.h"
#include "variant_util.h"

using Token = AsmToken::AsmToken;

template <typename T>
T AsmLexer::LexId() {
    T result;

    while ((s.peek() >= '0' && s.peek() <= '9') || (s.peek() >= 'a' && s.peek() <= 'z') || (s.peek() >= 'A' && s.peek() <= 'Z')) {
        int ch = s.get();
        result.value += (char)ch;
    }

    return result;
}

namespace AsmToken {
std::string ToString(const AsmToken& token) {
    return std::visit(overloaded {
        [](Error) -> std::string { return "Error"; },
        [](EndOfLine) -> std::string { return "EndOfLine"; },
        [](EndOfFile) -> std::string { return "EndOfFile"; },

        [](OpenBracket) -> std::string { return "OpenBracket"; },
        [](CloseBracket) -> std::string { return "CloseBracket"; },
        [](DoublePipe) -> std::string { return "DoublePipe"; },
        [](Colon) -> std::string { return "Colon"; },

        [](Numeric numeric) -> std::string {
            switch (numeric.size_marker) {
            case SizeMarker::Small:
                return "Numeric #" + std::to_string(numeric.value);
            case SizeMarker::Big:
                return "Numeric ##" + std::to_string(numeric.value);
            default:
                return "Numeric " + std::to_string(numeric.value);
            }
        },
        [](Identifier identifier) -> std::string { return "Identifier " + identifier.value; },
        [](Label label) -> std::string {
            switch (label.size_marker) {
            case SizeMarker::Small:
                return "Label #$" + label.value;
            case SizeMarker::Big:
                return "Label ##$" + label.value;
            default:
                return "Label $" + label.value;
            }
        },
        [](MetaStatement meta_statement) -> std::string { return "MetaStatement " + meta_statement.value; },
    }, token);
}
} // namespace AsmToken

AsmLexer::AsmLexer(std::istream& stream) : s(stream) {}

Token AsmLexer::PeekToken() {
    if (!current_token)
        current_token = NextToken();
    return *current_token;
}

Token AsmLexer::NextToken() {
    if (current_token) {
        return *std::exchange(current_token, std::nullopt);
    }

    SkipWhitespace();

    if (s.peek() == '\n') {
        start_of_line = true;
        s.get();
        return AsmToken::EndOfLine{};
    }
    if (s.peek() == EOF) {
        return AsmToken::EndOfFile{};
    }
    if ((s.peek() >= 'a' && s.peek() <= 'z') || (s.peek() >= 'A' && s.peek() <= 'Z')) {
        return LexId<AsmToken::Identifier>();
    }
    if (s.peek() == '#') {
        s.get();
        AsmToken::SizeMarker size_marker = AsmToken::SizeMarker::Small;
        if (s.peek() == '#') {
            s.get();
            size_marker = AsmToken::SizeMarker::Big;
        }
        if (s.peek() == '$') {
            s.get();
            auto result = LexId<AsmToken::Label>();
            result.size_marker = size_marker;
            return result;
        }
        if ((s.peek() >= '0' && s.peek() <= '9') || s.peek() == '-' || s.peek() == '+') {
            auto result = LexNumeric();
            if (result.size_marker != AsmToken::SizeMarker::None)
                return AsmToken::Error{};
            result.size_marker = size_marker;
            return result;
        }
        return AsmToken::Error{};
    }
    if ((s.peek() >= '0' && s.peek() <= '9') || s.peek() == '-' || s.peek() == '+') {
        return LexNumeric();
    }
    if (s.peek() == '$') {
        s.get();
        return LexId<AsmToken::Label>();
    }
    if (s.peek() == '.') {
        s.get();
        return LexId<AsmToken::MetaStatement>();
    }
    if (s.peek() == '[') {
        s.get();
        return AsmToken::OpenBracket{};
    }
    if (s.peek() == ']') {
        s.get();
        return AsmToken::CloseBracket{};
    }
    if (s.peek() == ',') {
        s.get();
        return AsmToken::Identifier{","};
    }
    if (s.peek() == '|') {
        s.get();
        if (s.get() == '|')
            return AsmToken::DoublePipe{};
        return AsmToken::Error{};
    }
    if (s.peek() == ':') {
        s.get();
        return AsmToken::Colon{};
    }
    if (s.peek() == '_') {
        s.get();
        return AsmToken::Identifier{"_"};
    }

    return AsmToken::Error{};
}

void AsmLexer::SkipWhitespace() {
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

AsmToken::Numeric AsmLexer::LexNumeric() {
    AsmToken::Numeric result;

    if (s.peek() == '+') {
        s.get();
        result.had_sign = true;
        SkipWhitespace();
    } else if (s.peek() == '-') {
        s.get();
        result.had_sign = true;
        result.is_negative = true;
        SkipWhitespace();
    }

    if (s.peek() == '#') {
        s.get();
        result.size_marker = AsmToken::SizeMarker::Small;
        if (s.peek() == '#') {
            s.get();
            result.size_marker = AsmToken::SizeMarker::Big;
        }
        SkipWhitespace();
    }

    if (!(s.peek() >= '0' && s.peek() <= '9')) {
        result.had_value = false;
        return result;
    }

    if (s.peek() == '0') {
        s.get();
        if (s.peek() == 'x') {
            s.get();
            while (true) {
                int ch = s.peek();
                if (ch >= '0' && ch <= '9') {
                    s.get();
                    result.value *= 0x10;
                    result.value += ch - '0';
                } else if (ch >= 'a' && ch <= 'f') {
                    s.get();
                    result.value *= 0x10;
                    result.value += ch - 'a' + 0xA;
                } else if (ch >= 'A' && ch <= 'F') {
                    s.get();
                    result.value *= 0x10;
                    result.value += ch - 'A' + 0xA;
                } else {
                    break;
                }
            }
            if (result.is_negative) {
                result.value *= -1;
            }
            return result;
        } else if (s.peek() == 'b') {
            s.get();
            while (true) {
                int ch = s.peek();
                if (ch >= '0' && ch <= '1') {
                    s.get();
                    result.value *= 0b10;
                    result.value += ch - '0';
                } else {
                    break;
                }
            }
            if (result.is_negative) {
                result.value *= -1;
            }
            return result;
        }
    }

    while (true) {
        int ch = s.peek();
        if (ch >= '0' && ch <= '9') {
            s.get();
            result.value *= 10;
            result.value += ch - '0';
        } else {
            break;
        }
    }
    if (result.is_negative) {
        result.value *= -1;
    }
    return result;
}
