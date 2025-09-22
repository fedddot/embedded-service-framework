add_executable(
	processor_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_processor.cpp
)

target_link_libraries(
	processor_tests
	PRIVATE
    processor
	ring_queue
    gtest
	gmock
	gtest_main
)

add_test(NAME processor_tests COMMAND processor_tests)