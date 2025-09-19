add_library(api_request_reader INTERFACE)
target_include_directories(api_request_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    api_request_reader
    INTERFACE
    data_reader
)

add_library(api_response_writer INTERFACE)
target_include_directories(api_response_writer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    api_response_writer
    INTERFACE
    data_writer
)

add_subdirectory(tests EXCLUDE_FROM_ALL)