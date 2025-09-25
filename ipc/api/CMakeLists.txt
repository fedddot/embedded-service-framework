add_library(api_message_reader INTERFACE)
target_include_directories(api_message_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    api_message_reader
    INTERFACE
    data_reader
)

add_library(api_message_writer INTERFACE)
target_include_directories(api_message_writer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    api_message_writer
    INTERFACE
    data_writer
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()