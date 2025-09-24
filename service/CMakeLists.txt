add_library(service INTERFACE)
target_include_directories(service INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(asynchronous_drive_service)