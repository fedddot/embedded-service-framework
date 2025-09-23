add_library(input_stream INTERFACE)
target_include_directories(input_stream INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(ring_buffer_input_stream INTERFACE)
target_include_directories(ring_buffer_input_stream INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ring_buffer_input_stream INTERFACE input_stream)

add_library(package_header INTERFACE)
target_include_directories(package_header INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(package_header_parser INTERFACE)
target_include_directories(package_header_parser INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(package_header_parser INTERFACE package_header)

add_library(package_header_serializer INTERFACE)
target_include_directories(package_header_serializer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(package_header_serializer INTERFACE package_header)

add_library(package_reader INTERFACE)
target_include_directories(package_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    package_reader
    INTERFACE
    data_reader
    input_stream
    package_header
)

add_library(package_writer INTERFACE)
target_include_directories(package_writer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    package_writer
    INTERFACE
    data_writer
    package_header
)

add_subdirectory(tests)