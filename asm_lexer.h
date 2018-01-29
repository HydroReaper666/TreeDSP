#pragma once

#include <istream>
#include <list>
#include <optional>
#include <string>
#include <variant>

namespace AsmToken {

enum class SizeMarker {
    None,
    Small,
    Big,
};

struct Error {};
struct EndOfLine {};
struct EndOfFile {};
struct OpenBracket {};
struct CloseBracket {};
struct DoublePipe {};
struct Colon {};

struct Numeric { 
    SizeMarker size_marker = SizeMarker::None; 
    bool had_sign = false;
    bool is_negative = false;
    bool had_value = true;
    std::int64_t value = 0;
};
struct Identifier { std::string value; };
struct Label {
    SizeMarker size_marker = SizeMarker::None; 
    std::string value;
};
struct MetaStatement { std::string value; };

using AsmToken = std::variant<
    Error,
    EndOfLine,
    EndOfFile,
    OpenBracket,
    CloseBracket,
    DoublePipe,
    Colon,
    Numeric,
    Identifier,
    Label,
    MetaStatement
>;

std::string ToString(const AsmToken& token);

} // namespace AsmToken

struct AsmLexer {
public:
    using Token = AsmToken::AsmToken;

    explicit AsmLexer(std::istream& stream);

    Token PeekToken();
    Token NextToken();

private:
    void SkipWhitespace();

    AsmToken::Numeric LexNumeric();
    template <typename T>
    T LexId();

    bool start_of_line = true;
    std::istream& s;
    std::optional<Token> current_token;
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
