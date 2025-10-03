add_subdirectory(nanopb-src ${CMAKE_CURRENT_BINARY_DIR}/nanopb-build)

add_library(nanopb_message_reader INTERFACE)
target_include_directories(nanopb_message_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    nanopb_message_reader
    INTERFACE
    data_reader
    protobuf-nanopb-static
)

add_library(nanopb_message_writer INTERFACE)
target_include_directories(nanopb_message_writer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    nanopb_message_writer
    INTERFACE
    data_writer
    protobuf-nanopb-static
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()