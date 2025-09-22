add_executable(
	queue_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_ring_queue.cpp
)

target_link_libraries(
	queue_tests
	PRIVATE
	ring_queue
	gtest
	gtest_main
)

add_test(NAME queue_tests COMMAND queue_tests)