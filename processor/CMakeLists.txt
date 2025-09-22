add_library(data_consumer INTERFACE)
target_include_directories(data_consumer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(data_consumer INTERFACE queue)

add_library(data_producer INTERFACE)
target_include_directories(data_producer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(data_producer INTERFACE queue)

add_library(processor INTERFACE)
target_include_directories(processor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(processor INTERFACE queue data_consumer data_producer)

add_subdirectory(tests)