#include "gtest/gtest.h"
#include <cstddef>

#include "asynchronous_drive_request.hpp"
#include "asynchronous_drive_service.hpp"

using namespace service;

TEST(ut_asynchronous_drive_service, run_api_request_sanity) {
	// GIVEN
	const auto test_speed_rpm = std::size_t(150);
	const auto test_start_request = AsynchronousDriveRequest(
		AsynchronousDriveRequest::Type::START,
		test_speed_rpm
	);
	
	// WHEN
	AsynchronousDriveService service;
	const auto response = service.run_api_request(test_start_request);
	
	// THEN
	EXPECT_EQ(response.result(), AsynchronousDriveResponse::Result::SUCCESS);
}