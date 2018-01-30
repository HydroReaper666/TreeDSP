add_executable(tdsp-tests
    main.cpp
)

include(CreateDirectoryGroups)
create_target_directory_groups(tdsp-tests)

target_link_libraries(tdsp-tests PRIVATE catch tdsp-lib)
target_include_directories(tdsp-tests PRIVATE .)

add_test(tdsp-tests tdsp-tests)
