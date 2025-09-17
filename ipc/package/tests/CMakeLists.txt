add_executable(
	package_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_ring_queue.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_package_reader.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_package_writer.cpp
)

target_link_libraries(
	package_tests
	PRIVATE
	ring_queue
	package_reader
	package_writer
	package_utils
	gtest
	gtest_main
)

add_test(NAME package_tests COMMAND package_tests)