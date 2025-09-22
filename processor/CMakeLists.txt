add_library(processor INTERFACE)
target_include_directories(processor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(processor INTERFACE queue)

add_subdirectory(tests)