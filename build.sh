set -e

clang++ --std=c++17 -g -O0 \
    asm_lexer.cpp \
    instruction_table_lexer.cpp \
    main.cpp

./a.out