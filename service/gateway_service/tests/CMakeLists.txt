add_executable(
	gateway_service_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_gateway_service.cpp
)

target_link_libraries(
	gateway_service_tests
	PRIVATE
    gateway_service
    gtest
	gmock
	gtest_main
)

add_test(NAME gateway_service_tests COMMAND gateway_service_tests)