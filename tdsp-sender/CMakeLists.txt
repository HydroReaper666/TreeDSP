add_executable(tdsp-sender
    main.cpp
)

include(CreateDirectoryGroups)
create_target_directory_groups(tdsp-sender)

target_link_libraries(tdsp-sender PRIVATE boost tdsp-lib)
target_include_directories(tdsp-sender PRIVATE .)
