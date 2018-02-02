add_executable(tdsp-asm
    main.cpp
)

include(CreateDirectoryGroups)
create_target_directory_groups(tdsp-asm)

target_link_libraries(tdsp-asm PRIVATE tdsp-lib)
target_include_directories(tdsp-asm PRIVATE .)
