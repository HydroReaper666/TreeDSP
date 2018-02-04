#pragma once

#include <istream>
#include <list>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace AsmToken {

enum class SizeMarker {
    None,
    Small,
    Big,
};

struct Error {
    size_t byte_position;
};
struct EndOfLine {
    size_t byte_position;
};
struct EndOfFile {
    size_t byte_position;
};
struct OpenBracket {
    size_t byte_position;
};
struct CloseBracket {
    size_t byte_position;
};
struct DoublePipe {
    size_t byte_position;
};
struct Colon {
    size_t byte_position;
};
struct Comma {
    size_t byte_position;
};

struct Numeric { 
    size_t byte_position;
    SizeMarker size_marker = SizeMarker::None; 
    bool had_sign = false;
    bool is_negative = false;
    bool had_value = true;
    std::int64_t value = 0;
};
struct Identifier {
    size_t byte_position;
    std::string value;
};
struct Label {
    size_t byte_position;
    SizeMarker size_marker = SizeMarker::None; 
    std::string value;
};
struct MetaStatement {
    size_t byte_position;
    std::string value;
};

using AsmToken = std::variant<
    Error,
    EndOfLine,
    EndOfFile,
    OpenBracket,
    CloseBracket,
    DoublePipe,
    Colon,
    Comma,
    Numeric,
    Identifier,
    Label,
    MetaStatement
>;

std::string ToString(const AsmToken& token);

} // namespace AsmToken

struct TokenPosition {
    size_t byte_position;
    size_t line;
    size_t column;
};

struct AsmLexer {
public:
    using Token = AsmToken::AsmToken;

    explicit AsmLexer(std::istream& stream);

    Token PeekToken();
    Token NextToken();

    TokenPosition GetPositionOf(const Token& token) const;

private:
    void SkipWhitespace();

    AsmToken::Numeric LexNumeric(size_t byte_position);
    template <typename T>
    T LexId(size_t byte_position);

    int Peek();
    int Get();

    bool start_of_line = true;
    std::istream& s;
    std::optional<Token> current_token;
    size_t byte_position = 0;
    std::vector<size_t> line_begin_pos;
};

using TokenList = std::list<AsmToken::AsmToken>;

inline std::optional<TokenList> GetLine(AsmLexer& lexer) {
    TokenList result;
    while (true) {
        auto token = lexer.NextToken();
        if (std::holds_alternative<AsmToken::EndOfFile>(token) || std::holds_alternative<AsmToken::EndOfLine>(token))
            return result;
        if (std::holds_alternative<AsmToken::Error>(token))
            return std::nullopt;
        result.push_back(token);
    }
}
