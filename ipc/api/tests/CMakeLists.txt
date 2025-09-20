add_executable(
	ipc_api_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_api_message_reader.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_api_message_writer.cpp
)

target_link_libraries(
	ipc_api_tests
	PRIVATE
	api_message_reader
	api_message_writer
	gtest
	gmock
	gtest_main
)

add_test(NAME ipc_api_tests COMMAND ipc_api_tests)