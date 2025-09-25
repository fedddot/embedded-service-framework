add_library(cnc_service_api_request INTERFACE)
target_include_directories(cnc_service_api_request INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(cnc_service_api_response INTERFACE)
target_include_directories(cnc_service_api_response INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(cnc_service INTERFACE)
target_include_directories(cnc_service INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    cnc_service
    INTERFACE
    service
    cnc_service_api_request
    cnc_service_api_response
)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()