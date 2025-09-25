add_library(gateway_service_types INTERFACE)
target_include_directories(gateway_service_types INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(gateway_service_api_request INTERFACE)
target_include_directories(gateway_service_api_request INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(gateway_service_api_request INTERFACE gateway_service_types)

add_library(gateway_service_api_response INTERFACE)
target_include_directories(gateway_service_api_response INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(gateway_service_api_response INTERFACE gateway_service_types)

add_library(gateway_service INTERFACE)
target_include_directories(gateway_service INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
    gateway_service
    INTERFACE
    service
    gateway_service_api_request
    gateway_service_api_response
)
add_subdirectory(tests)