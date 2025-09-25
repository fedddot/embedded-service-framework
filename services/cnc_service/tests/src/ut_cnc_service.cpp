#include "gtest/gtest.h"

#include "cnc_service.hpp"
#include "cnc_service_api_request.hpp"
#include "cnc_service_api_response.hpp"
#include "linear_movement_data.hpp"

using namespace service;

TEST(ut_cnc_service, run_api_request_sanity) {
	// GIVEN
	const LinearMovementData test_movement_data(
		Vector<double>(0.0, 0.0, 0.0),
		Vector<double>({10.0, 10.0, 10.0}),
		100.0
	);
	const CncServiceApiRequest test_request(
		CncServiceApiRequest::MovementType::LINEAR,
		std::nullopt,
		test_movement_data
	);
	// WHEN:
	CncService service;
	
	// THEN:
	const auto response = service.run_api_request(test_request);
	ASSERT_EQ(response.result(), CncServiceApiResponse::Result::SUCCESS);
}