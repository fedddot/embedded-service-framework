set(TEST_GENERATED_API_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
	OUTPUT ${TEST_GENERATED_API_DIR}/test.pb.c ${TEST_GENERATED_API_DIR}/test.pb.h
	DEPENDS ${CMAKE_CURRENT_LIST_DIR}/res/test.proto
	COMMAND python ${CMAKE_CURRENT_LIST_DIR}/../nanopb-src/generator/nanopb_generator.py -I ${CMAKE_CURRENT_LIST_DIR}/res -D ${TEST_GENERATED_API_DIR} test.proto
)

add_custom_target(
	generate_test_api
	DEPENDS ${TEST_GENERATED_API_DIR}/test.pb.c ${TEST_GENERATED_API_DIR}/test.pb.h
)

add_library(test_api INTERFACE)
add_dependencies(test_api generate_test_api)
target_sources(test_api INTERFACE ${TEST_GENERATED_API_DIR}/test.pb.c)
target_include_directories(test_api INTERFACE ${TEST_GENERATED_API_DIR})

add_executable(
	ipc_nanopb_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_nanopb_message_reader.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_nanopb_message_writer.cpp
)

target_link_libraries(
	ipc_nanopb_tests
	PRIVATE
	test_api
	nanopb_message_reader
	nanopb_message_writer
	gtest
	gmock
	gtest_main
)

add_test(NAME ipc_nanopb_tests COMMAND ipc_nanopb_tests)