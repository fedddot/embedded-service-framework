add_executable(
	package_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_ring_buffer_input_stream.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_package_reader.cpp
	# ${CMAKE_CURRENT_LIST_DIR}/src/ut_package_writer.cpp
)

target_link_libraries(
	package_tests
	PRIVATE
	ring_buffer_input_stream
	package_reader
	package_header_parser
	package_header_serializer
	package_writer
	gtest
	gtest_main
)

add_test(NAME package_tests COMMAND package_tests)