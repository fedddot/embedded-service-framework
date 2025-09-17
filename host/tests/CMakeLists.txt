add_executable(
	host_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_host.cpp
)

target_link_libraries(
	host_tests
	PRIVATE
    host
    gtest
	gmock
	gtest_main
)

add_test(NAME host_tests COMMAND host_tests)