add_library(gateway_service INTERFACE)
target_include_directories(gateway_service INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    gateway_service
    INTERFACE
    service
)
add_subdirectory(tests)