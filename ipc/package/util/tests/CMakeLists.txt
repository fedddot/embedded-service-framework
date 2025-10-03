add_executable(
	ipc_package_util_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_ring_buffer_input_stream.cpp
)

target_link_libraries(
	ipc_package_util_tests
	PRIVATE
	ring_buffer_input_stream
	gtest
	gtest_main
)

add_test(NAME ipc_package_util_tests COMMAND ipc_package_util_tests)