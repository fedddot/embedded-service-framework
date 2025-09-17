add_library(host INTERFACE)
target_include_directories(host INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    host
    INTERFACE
    data_reader
    data_writer
    service
)

add_subdirectory(tests)