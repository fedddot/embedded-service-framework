#include "gtest/gtest.h"

#include "motor_drive_service.hpp"
#include "motor_drive_service_api_request.hpp"

using namespace service;

enum class TestRouteId {
	TEST_ROUTE_0 = 0,
	TEST_ROUTE_1 = 1,
};

using TestPayload = std::string;

TEST(ut_motor_drive_service, run_api_request_sanity) {
	// GIVEN
	const TestPayload request_payload("request_payload");
	const TestPayload expected_response_payload("response_payload");
	const TestRouteId route_id = TestRouteId::TEST_ROUTE_0;
	const MotorDriveServiceApiRequest<TestRouteId, TestPayload> test_request(
		route_id,
		request_payload
	);

	// WHEN:
	MotorDriveService<TestRouteId, TestPayload> service;
	service.register_route_handler(
		route_id,
		[expected_request_payload = request_payload, expected_response_payload](const TestPayload& request_payload) {
			if (request_payload != expected_request_payload) {
				throw std::invalid_argument("unexpected payload received in handler");
			}
			return expected_response_payload;
		}
	);

	// THEN:
	const auto response = service.run_api_request(test_request);
	ASSERT_EQ(response.route_id(), route_id);
	ASSERT_EQ(response.payload(), expected_response_payload);
}