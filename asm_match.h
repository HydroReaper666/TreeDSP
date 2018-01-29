#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <variant>

#include "asm_lexer.h"

template <typename T>
inline std::optional<T> Match(TokenList& tl) {
    if (tl.empty())
        return std::nullopt;

    if (!std::holds_alternative<T>(tl.front()))
        return std::nullopt;

    auto token = tl.front();
    tl.pop_front();
    return std::get<T>(token);
}

inline bool MatchIdentifier(TokenList& tl, const std::string& s) {
    if (auto identifier = Match<AsmToken::Identifier>(tl))
        if (identifier->value == s)
            return true;
    return false;
}

inline std::optional<size_t> MatchIdentifierSet(TokenList& tl, const std::vector<std::string>& v) {
    if (auto identifier = Match<AsmToken::Identifier>(tl))
        for (size_t i = 0; i < v.size(); ++i)
            if (identifier->value == v[i])
                return i;
    return std::nullopt;
}

inline std::optional<std::uint32_t> MatchNumeric(TokenList& tl, bool signed_, size_t bit_size) {
    if (auto numeric = Match<AsmToken::Numeric>(tl)) {
        if (!signed_ && numeric->value < (1 << bit_size) && numeric->value >= 0)
            return static_cast<std::uint32_t>(numeric->value);
        if (signed_ && numeric->value < (1 << (bit_size - 1)) && numeric->value >= -(1 << (bit_size - 1)))
            return static_cast<std::uint32_t>(numeric->value) & ((1 << bit_size) - 1);
    }
    return std::nullopt;
}
