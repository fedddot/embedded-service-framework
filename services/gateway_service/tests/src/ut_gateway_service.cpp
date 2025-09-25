#include "gtest/gtest.h"

#include "gateway_service.hpp"
#include "gateway_service_api_request.hpp"

using namespace service;

TEST(ut_gateway_service, run_api_request_sanity) {
	// GIVEN
	const GatewayServiceApiRequest test_request;

	// WHEN:
	GatewayService service;

	// THEN:
	const auto response = service.run_api_request(test_request);
}