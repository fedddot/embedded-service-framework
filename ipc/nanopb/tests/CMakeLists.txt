add_executable(
	ipc_nanopb_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_nanopb_message_reader.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_nanopb_message_writer.cpp
)

target_link_libraries(
	ipc_nanopb_tests
	PRIVATE
	nanopb_message_reader
	nanopb_message_writer
	gtest
	gmock
	gtest_main
)

add_test(NAME ipc_nanopb_tests COMMAND ipc_nanopb_tests)