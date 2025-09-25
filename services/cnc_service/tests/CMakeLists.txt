add_executable(
	cnc_service_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_cnc_service.cpp
)

target_link_libraries(
	cnc_service_tests
	PRIVATE
    cnc_service
    cnc_service_api_request
    cnc_service_api_response
    linear_movement_data
    gtest
	gmock
	gtest_main
)

add_test(NAME cnc_service_tests COMMAND cnc_service_tests)