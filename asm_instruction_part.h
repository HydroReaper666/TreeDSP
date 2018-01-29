#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>

#include "asm_match.h"
#include "bit_util.h"

class AsmInstructionPart {
public:
    virtual ~AsmInstructionPart() = default;

    virtual std::optional<std::uint32_t> Parse(TokenList& tl) const = 0;
    virtual std::uint32_t GetMask() const = 0;
};

class SingleIdentifierPart : public AsmInstructionPart {
public:
    explicit SingleIdentifierPart(const std::string& s) : s(s) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        if (MatchIdentifier(tl, s))
            return 0;
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return 0;
    }

private:
    std::string s;
};

class SetOfIdentifierPart : public AsmInstructionPart {
public:
    SetOfIdentifierPart(const std::vector<std::string>& v, size_t bit_pos, bool invert = false) : v(v), bit_pos(bit_pos), invert(invert) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        if (auto i = MatchIdentifierSet(tl, v)) {
            std::uint32_t bits = *i << bit_pos;
            if (invert) {
                bits = bits ^ GetMask();
            }
            return bits;
        }
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return Ones<std::uint32_t>(Log2(v.size())) << bit_pos;
    }

private:
    std::vector<std::string> v;
    size_t bit_pos;
    bool invert;
};

template <typename T>
class TokenTypePart : public AsmInstructionPart {
public:
    explicit TokenTypePart() {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        if (Match<T>(tl))
            return 0;
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return 0;
    }
};

const std::vector<std::string> set_Rn { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7" };
const std::vector<std::string> set_Ax { "a0", "a1" };
const std::vector<std::string> set_Axl { "a0l", "a1l" };
const std::vector<std::string> set_Axh { "a0h", "a1h" };
const std::vector<std::string> set_Bx { "b0", "b1" };
const std::vector<std::string> set_Bxl { "b0l", "b1l" };
const std::vector<std::string> set_Bxh { "b0h", "b1h" };
const std::vector<std::string> set_Ab { "b0", "b1", "a0", "a1" };
const std::vector<std::string> set_Abl { "b0l", "b1l", "a0l", "a1l" };
const std::vector<std::string> set_Abh { "b0h", "b1h", "a0h", "a1h" };
const std::vector<std::string> set_Abe { "b0e", "b1e", "a0e", "a1e" };
const std::vector<std::string> set_Px { "p0", "p1" };
const std::vector<std::string> set_Ablh { "b0l", "b0h", "b1l", "b1h", "a0l", "a0h", "a1l", "a1h" };
const std::vector<std::string> set_Cond { "true", "eq", "neq", "gt", "ge", "lt", "le", "nn", "c", "v", "e", "l", "nr", "niu0", "iu0", "iu1" };

// not
class Not : public AsmInstructionPart {
public:
    explicit Not(std::shared_ptr<AsmInstructionPart> instruction_part) : instruction_part(instruction_part) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        if (auto result = instruction_part->Parse(tl)) {
            return *result ^ GetMask();
        }
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return instruction_part->GetMask();
    }

private:
    std::shared_ptr<AsmInstructionPart> instruction_part;
};

// [sp]
class MemSp : public AsmInstructionPart {
public:
    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "sp"))
            return std::nullopt;
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0;
    }
};

// [Rn]
class MemRn : public AsmInstructionPart {
public:
    explicit MemRn(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (auto i = MatchIdentifierSet(tl, set_Rn)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0b111 << bit_pos;
    }

private:
    size_t bit_pos;
};

// [code:movpd:Rn]
class ProgMemRn : public AsmInstructionPart {
public:
    explicit ProgMemRn(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "code"))
            return std::nullopt;
        if (!Match<AsmToken::Colon>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "movpd"))
            return std::nullopt;
        if (!Match<AsmToken::Colon>(tl))
            return std::nullopt;
        if (auto i = MatchIdentifierSet(tl, set_Rn)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0b111 << bit_pos;
    }

private:
    size_t bit_pos;
};

// [code:movpd:Axl]
class ProgMemAxl : public AsmInstructionPart {
public:
    explicit ProgMemAxl(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "code"))
            return std::nullopt;
        if (!Match<AsmToken::Colon>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "movpd"))
            return std::nullopt;
        if (!Match<AsmToken::Colon>(tl))
            return std::nullopt;
        if (auto i = MatchIdentifierSet(tl, set_Axl)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0b1 << bit_pos;
    }

private:
    size_t bit_pos;
};

// [code:Ax]
class ProgMemAx : public AsmInstructionPart {
public:
    explicit ProgMemAx(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "code"))
            return std::nullopt;
        if (!Match<AsmToken::Colon>(tl))
            return std::nullopt;
        if (auto i = MatchIdentifierSet(tl, set_Ax)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0b1 << bit_pos;
    }

private:
    size_t bit_pos;
};

// [page:0xNN]
class MemImm8 : public AsmInstructionPart {
public:
    explicit MemImm8(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "page"))
            return std::nullopt;
        if (!Match<AsmToken::Colon>(tl))
            return std::nullopt;
        if (auto i = MatchNumeric(tl, false, 8)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0xFF << bit_pos;
    }

private:
    size_t bit_pos;
};

// [0xNNNN]
class MemImm16 : public AsmInstructionPart {
public:
    explicit MemImm16(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (auto i = MatchNumeric(tl, false, 16)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0xFFFF << bit_pos;
    }

private:
    size_t bit_pos;
};

// [r7+/-0xNN]
class MemR7Imm7s : public AsmInstructionPart {
public:
    explicit MemR7Imm7s(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "r7"))
            return std::nullopt;
        if (auto i = MatchNumeric(tl, true, 7)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0x7F << bit_pos;
    }

private:
    size_t bit_pos;
};

// [r7+0xNNNN]
class MemR7Imm16 : public AsmInstructionPart {
public:
    explicit MemR7Imm16(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "r7"))
            return std::nullopt;
        if (auto i = MatchNumeric(tl, false, 16)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return result;
    }

    std::uint32_t GetMask() const override {
        return 0xFFFF << bit_pos;
    }

private:
    size_t bit_pos;
};

template <size_t size>
class ImmU : public AsmInstructionPart {
public:
    explicit ImmU(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto i = MatchNumeric(tl, false, size)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        return result;
    }

    std::uint32_t GetMask() const override {
        return Ones<std::uint32_t>(size) << bit_pos;
    }

private:
    size_t bit_pos;
};

template <size_t size>
class ImmS : public AsmInstructionPart {
public:
    explicit ImmS(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<std::uint32_t> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto i = MatchNumeric(tl, true, size)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        return result;
    }

    std::uint32_t GetMask() const override {
        return Ones<std::uint32_t>(size) << bit_pos;
    }

private:
    size_t bit_pos;
};

using Imm8u = ImmU<8>;
using Imm16 = ImmU<16>;
