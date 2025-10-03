add_library(data_reader INTERFACE)
target_include_directories(data_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(data_writer INTERFACE)
target_include_directories(data_writer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(api)
add_subdirectory(nanopb)
add_subdirectory(package)