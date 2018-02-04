#include <algorithm>
#include <iterator>

#include "asm_lexer.h"
#include "variant_util.h"

using Token = AsmToken::AsmToken;

template <typename T>
T AsmLexer::LexId(size_t current_position) {
    T result;
    result.byte_position = current_position;

    while ((Peek() >= '0' && Peek() <= '9') || (Peek() >= 'a' && Peek() <= 'z') || (Peek() >= 'A' && Peek() <= 'Z')) {
        int ch = Get();
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
        [](Comma) -> std::string { return "Comma"; },

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

AsmLexer::AsmLexer(std::istream& stream) : s(stream) {
    line_begin_pos.push_back(0);
}

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

    const size_t current_position = byte_position;

    if (Peek() == '\n') {
        start_of_line = true;
        Get();
        line_begin_pos.push_back(byte_position);
        return AsmToken::EndOfLine{current_position};
    }
    if (Peek() == EOF) {
        return AsmToken::EndOfFile{current_position};
    }
    if ((Peek() >= 'a' && Peek() <= 'z') || (Peek() >= 'A' && Peek() <= 'Z')) {
        return LexId<AsmToken::Identifier>(current_position);
    }
    if (Peek() == '#') {
        Get();
        AsmToken::SizeMarker size_marker = AsmToken::SizeMarker::Small;
        if (Peek() == '#') {
            Get();
            size_marker = AsmToken::SizeMarker::Big;
        }
        if (Peek() == '$') {
            Get();
            auto result = LexId<AsmToken::Label>(current_position);
            result.size_marker = size_marker;
            return result;
        }
        if ((Peek() >= '0' && Peek() <= '9') || Peek() == '-' || Peek() == '+') {
            auto result = LexNumeric(current_position);
            if (result.size_marker != AsmToken::SizeMarker::None)
                return AsmToken::Error{current_position};
            result.size_marker = size_marker;
            return result;
        }
        return AsmToken::Error{current_position};
    }
    if ((Peek() >= '0' && Peek() <= '9') || Peek() == '-' || Peek() == '+') {
        return LexNumeric(current_position);
    }
    if (Peek() == '$') {
        Get();
        return LexId<AsmToken::Label>(current_position);
    }
    if (Peek() == '.') {
        Get();
        return LexId<AsmToken::MetaStatement>(current_position);
    }
    if (Peek() == '[') {
        Get();
        return AsmToken::OpenBracket{current_position};
    }
    if (Peek() == ']') {
        Get();
        return AsmToken::CloseBracket{current_position};
    }
    if (Peek() == ',') {
        Get();
        return AsmToken::Comma{current_position};
    }
    if (Peek() == '|') {
        Get();
        if (Get() == '|')
            return AsmToken::DoublePipe{current_position};
        return AsmToken::Error{current_position};
    }
    if (Peek() == ':') {
        Get();
        return AsmToken::Colon{current_position};
    }
    if (Peek() == '_') {
        Get();
        return AsmToken::Identifier{current_position, "_"};
    }

    return AsmToken::Error{current_position};
}

TokenPosition AsmLexer::GetPositionOf(const Token& token) const {
    const size_t byte_position = std::visit([](const auto& t) { return t.byte_position; }, token);
    const auto iter = std::prev(std::upper_bound(line_begin_pos.begin(), line_begin_pos.end(), byte_position));
    TokenPosition result;
    result.byte_position = byte_position;
    result.line = std::distance(line_begin_pos.begin(), iter) + 1;
    result.column = byte_position - *iter + 1;
    return result;
}

void AsmLexer::SkipWhitespace() {
    while (Peek() == ' ' || Peek() == '\t' || Peek() == '\r') {
        Get();
    }

    // Comment til end of line
    if (Peek() == ';') {
        while (Peek() != '\n') {
            Get();
        }
    }
}

AsmToken::Numeric AsmLexer::LexNumeric(size_t current_position) {
    AsmToken::Numeric result;
    result.byte_position = current_position;

    if (Peek() == '+') {
        Get();
        result.had_sign = true;
        SkipWhitespace();
    } else if (Peek() == '-') {
        Get();
        result.had_sign = true;
        result.is_negative = true;
        SkipWhitespace();
    }

    if (Peek() == '#') {
        Get();
        result.size_marker = AsmToken::SizeMarker::Small;
        if (Peek() == '#') {
            Get();
            result.size_marker = AsmToken::SizeMarker::Big;
        }
        SkipWhitespace();
    }

    if (!(Peek() >= '0' && Peek() <= '9')) {
        result.had_value = false;
        return result;
    }

    if (Peek() == '0') {
        Get();
        if (Peek() == 'x') {
            Get();
            while (true) {
                int ch = Peek();
                if (ch >= '0' && ch <= '9') {
                    Get();
                    result.value *= 0x10;
                    result.value += ch - '0';
                } else if (ch >= 'a' && ch <= 'f') {
                    Get();
                    result.value *= 0x10;
                    result.value += ch - 'a' + 0xA;
                } else if (ch >= 'A' && ch <= 'F') {
                    Get();
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
        } else if (Peek() == 'b') {
            Get();
            while (true) {
                int ch = Peek();
                if (ch >= '0' && ch <= '1') {
                    Get();
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
        int ch = Peek();
        if (ch >= '0' && ch <= '9') {
            Get();
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

int AsmLexer::Peek() {
    return s.peek();
}

int AsmLexer::Get() {
    byte_position++;
    return s.get();
}
