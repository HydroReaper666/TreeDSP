#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <stdexcept>

#include "asm_match.h"
#include "bit_util.h"

struct SetBits {
    std::uint32_t bits = 0;
    std::uint32_t mask = 0;
};

class AsmInstructionPart {
public:
    virtual ~AsmInstructionPart() = default;

    virtual std::optional<SetBits> Parse(TokenList& tl) const = 0;
    virtual std::uint32_t GetMask() const = 0;
    virtual void CombineWith(std::shared_ptr<AsmInstructionPart> next) {
        throw std::logic_error("Invalid AsmInstructionPart::CombineWith");
    }
};

class SingleIdentifierPart : public AsmInstructionPart {
public:
    explicit SingleIdentifierPart(const std::string& s) : s(s) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        if (MatchIdentifier(tl, s))
            return SetBits{0, 0};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
        if (auto i = MatchIdentifierSet(tl, v)) {
            std::uint32_t bits = *i << bit_pos;
            if (invert) {
                bits = bits ^ GetMask();
            }
            return SetBits{bits, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
        if (Match<T>(tl))
            return SetBits{0, 0};
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
const std::vector<std::string> set_Register { "r0", "r1", "r2", "r3", "r4", "r5", "r7", "y0", "st0", "st1", "st2", "p0h", "pc", "sp", "cfgi", "cfgj", "b0h", "b1h", "b0l", "b1l", "ext0", "ext1", "ext2", "ext3", "a0", "a1", "a0l", "a1l", "a0h", "a1h", "lc", "sv" };
const std::vector<std::string> set_RegisterP0 { "r0", "r1", "r2", "r3", "r4", "r5", "r7", "y0", "st0", "st1", "st2", "p0", "pc", "sp", "cfgi", "cfgj", "b0h", "b1h", "b0l", "b1l", "ext0", "ext1", "ext2", "ext3", "a0", "a1", "a0l", "a1l", "a0h", "a1h", "lc", "sv" };
const std::vector<std::string> set_R0123457y0 { "r0", "r1", "r2", "r3", "r4", "r5", "r7", "y0" };
const std::vector<std::string> set_R01 { "r0", "r1" };
const std::vector<std::string> set_R04 { "r0", "r4" };
const std::vector<std::string> set_R45 { "r4", "r5" };
const std::vector<std::string> set_R0123 { "r0", "r1", "r2", "r3" };
const std::vector<std::string> set_R0425 { "r0", "r4", "r2", "r5" };
const std::vector<std::string> set_R4567 { "r4", "r5", "r6", "r7" };
const std::vector<std::string> set_ArArpSttMod { "ar0", "ar1", "arp0", "arp1", "arp2", "arp3", "-", "-", "stt0", "stt1", "stt2", "-", "mod0", "mod1", "mod2", "mod3" };
const std::vector<std::string> set_ArArp { "ar0", "ar1", "arp0", "arp1", "arp2", "arp3", "-", "-" };
const std::vector<std::string> set_SttMod { "stt0", "stt1", "stt2", "-", "mod0", "mod1", "mod2", "mod3" };
const std::vector<std::string> set_Ar { "ar0", "ar1" };
const std::vector<std::string> set_Arp { "arp0", "arp1", "arp2", "arp3" };

// not
class Not : public AsmInstructionPart {
public:
    explicit Not(std::shared_ptr<AsmInstructionPart> instruction_part) : instruction_part(instruction_part) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        if (auto result = instruction_part->Parse(tl)) {
            return SetBits{result->bits ^ result->mask, result->mask};
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
    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "sp"))
            return std::nullopt;
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return SetBits{result, GetMask()};
    }

    std::uint32_t GetMask() const override {
        return 0;
    }
};

// [r0]
class MemR0 : public AsmInstructionPart {
public:
    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (!MatchIdentifier(tl, "r0"))
            return std::nullopt;
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return SetBits{result, GetMask()};
    }

    std::uint32_t GetMask() const override {
        return 0;
    }
};

// [register]
// [register+/-offs]
template <const std::vector<std::string>& set>
class MemRx : public AsmInstructionPart {
public:
    explicit MemRx(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        std::uint32_t mask = GetMask();
        if (!Match<AsmToken::OpenBracket>(tl))
            return std::nullopt;
        if (auto i = MatchIdentifierSet(tl, set)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        if (offs) {
            if (auto offs_result = offs->Parse(tl)) {
                assert((mask & offs_result->mask) == 0);
                result |= offs_result->bits;
                mask |= offs_result->mask;
            } else {
                return std::nullopt;
            }
        }
        if (!Match<AsmToken::CloseBracket>(tl))
            return std::nullopt;
        return SetBits{result, mask};
    }

    std::uint32_t GetMask() const override {
        return Ones<std::uint32_t>(Log2(set.size())) << bit_pos;
    }

    virtual void CombineWith(std::shared_ptr<AsmInstructionPart> next) override {
        offs = next;
    }

private:
    size_t bit_pos;
    std::shared_ptr<AsmInstructionPart> offs;
};

using MemR01 = MemRx<set_R01>;
using MemR0123 = MemRx<set_R0123>;
using MemR04 = MemRx<set_R04>;
using MemR0425 = MemRx<set_R0425>;
using MemR45 = MemRx<set_R45>;
using MemR4567 = MemRx<set_R4567>;
using MemRn = MemRx<set_Rn>;

// [code:movpd:Rn]
class ProgMemRn : public AsmInstructionPart {
public:
    explicit ProgMemRn(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
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
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
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
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
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
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
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
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
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
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
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
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
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
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto i = MatchNumeric(tl, false, size)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        return SetBits{result, GetMask()};
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

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto i = MatchNumeric(tl, true, size)) {
            result = *i << bit_pos;
        } else {
            return std::nullopt;
        }
        return SetBits{result, GetMask()};
    }

    std::uint32_t GetMask() const override {
        return Ones<std::uint32_t>(size) << bit_pos;
    }

private:
    size_t bit_pos;
};

using Imm8u = ImmU<8>;
using Imm16 = ImmU<16>;

class stepZIDS : public AsmInstructionPart {
public:
    explicit stepZIDS(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (numeric->had_value) {
                switch (numeric->value) {
                case 0:
                    return SetBits{0u << bit_pos, GetMask()};
                case +1:
                    return SetBits{1u << bit_pos, GetMask()};
                case -1:
                    return SetBits{2u << bit_pos, GetMask()};
                }
                return std::nullopt;
            }
            if (numeric->is_negative)
                return std::nullopt;
            if (!MatchIdentifier(tl, "s"))
                return std::nullopt;
            return SetBits{3u << bit_pos, GetMask()};
        }
        return SetBits{0u << bit_pos, GetMask()};
    }

    std::uint32_t GetMask() const override {
        return 0b11 << bit_pos;
    }

private:
    size_t bit_pos;
};

using modrstepZIDS = stepZIDS;

class stepII2D2S : public AsmInstructionPart {
public:
    explicit stepII2D2S(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (numeric->had_value) {
                switch (numeric->value) {
                case +1:
                    return SetBits{0u << bit_pos, GetMask()};
                case +2:
                    return SetBits{1u << bit_pos, GetMask()};
                case -2:
                    return SetBits{2u << bit_pos, GetMask()};
                }
                return std::nullopt;
            }
            if (numeric->is_negative)
                return std::nullopt;
            if (!MatchIdentifier(tl, "s"))
                return std::nullopt;
            return SetBits{3u << bit_pos, GetMask()};
        }
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return 0b11 << bit_pos;
    }

private:
    size_t bit_pos;
};

using modrstepII2D2S0 = stepII2D2S;

class stepII2 : public AsmInstructionPart {
public:
    explicit stepII2(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (!numeric->had_value)
                return std::nullopt;
            switch (numeric->value) {
            case +1:
                return SetBits{0u << bit_pos, GetMask()};
            case +2:
                return SetBits{1u << bit_pos, GetMask()};
            }
            return std::nullopt;
        }
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return 0b1 << bit_pos;
    }

private:
    size_t bit_pos;
};

class modrstepI2 : public AsmInstructionPart {
public:
    explicit modrstepI2(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (!numeric->had_value)
                return std::nullopt;
            if (numeric->value != +2)
                return std::nullopt;
            return SetBits{0, 0};
        }
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return 0;
    }

private:
    size_t bit_pos;
};

class modrstepD2 : public AsmInstructionPart {
public:
    explicit modrstepD2(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (!numeric->had_value)
                return std::nullopt;
            if (numeric->value != -2)
                return std::nullopt;
            return SetBits{0, 0};
        }
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return 0;
    }

private:
    size_t bit_pos;
};

class offsZI : public AsmInstructionPart {
public:
    explicit offsZI(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (!numeric->had_value)
                return std::nullopt;
            switch (numeric->value) {
            case 0:
                return SetBits{0u << bit_pos, GetMask()};
            case +1:
                return SetBits{1u << bit_pos, GetMask()};
            }
            return std::nullopt;
        }
        return SetBits{0u << bit_pos, GetMask()};
    }

    std::uint32_t GetMask() const override {
        return 0b1 << bit_pos;
    }

private:
    size_t bit_pos;
};

class offsI : public AsmInstructionPart {
public:
    explicit offsI(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (!numeric->had_value)
                return std::nullopt;
            if (numeric->value != +1)
                return std::nullopt;
            return SetBits{0, 0};
        }
        return std::nullopt;
    }

    std::uint32_t GetMask() const override {
        return 0;
    }

private:
    size_t bit_pos;
};

class offsZIDZ : public AsmInstructionPart {
public:
    explicit offsZIDZ(size_t bit_pos) : bit_pos(bit_pos) {}

    std::optional<SetBits> Parse(TokenList& tl) const override {
        std::uint32_t result = 0;
        if (auto numeric = Match<AsmToken::Numeric>(tl)) {
            if (!numeric->had_sign)
                return std::nullopt;
            if (numeric->had_value) {
                switch (numeric->value) {
                case 0:
                    return SetBits{0, 0}; // 0 or 3
                case +1:
                    return SetBits{1u << bit_pos, GetMask()};
                case -1:
                    return SetBits{2u << bit_pos, GetMask()};
                }
            }
            return std::nullopt;
        }
        return SetBits{0, 0}; // 0 or 3
    }

    std::uint32_t GetMask() const override {
        return 0b11 << bit_pos;
    }

private:
    size_t bit_pos;
};
