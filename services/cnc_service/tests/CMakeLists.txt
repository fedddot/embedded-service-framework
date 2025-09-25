add_executable(
	cnc_service_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_cnc_service.cpp
)

target_link_libraries(
	cnc_service_tests
	PRIVATE
    cnc_service
    gtest
	gmock
	gtest_main
)

add_test(NAME cnc_service_tests COMMAND cnc_service_tests)