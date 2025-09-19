add_executable(
	ipc_api_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_api_request_reader.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_api_response_writer.cpp
)

target_link_libraries(
	ipc_api_tests
	PRIVATE
	api_request_reader
	api_response_writer
	gtest
	gtest_main
)