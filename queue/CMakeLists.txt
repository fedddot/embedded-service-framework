add_library(queue INTERFACE)
target_include_directories(queue INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(ring_queue INTERFACE)
target_include_directories(ring_queue INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ring_queue INTERFACE queue)

add_subdirectory(tests)