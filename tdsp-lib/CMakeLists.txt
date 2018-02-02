add_library(tdsp-lib STATIC
    asm_instruction_part.h
    asm_lexer.cpp
    asm_lexer.h
    asm_match.h
    asm_parse.cpp
    asm_parse.h
    bit_util.h
    instruction_table.inc
    instruction_table_lexer.cpp
    instruction_table_lexer.h
    part_parse_result.h
    sha256.cpp
    sha256.h
    variant_util.h
)

include(CreateDirectoryGroups)
create_target_directory_groups(tdsp-lib)

target_include_directories(tdsp-lib PUBLIC .)
