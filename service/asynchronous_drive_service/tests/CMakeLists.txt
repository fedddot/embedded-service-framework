add_executable(
	asynchronous_drive_service_tests
	${CMAKE_CURRENT_LIST_DIR}/src/ut_asynchronous_drive_service.cpp
)

target_link_libraries(
	asynchronous_drive_service_tests
	PRIVATE
	asynchronous_drive_service
	gtest
	gtest_main
)

add_test(NAME asynchronous_drive_service_tests COMMAND asynchronous_drive_service_tests)