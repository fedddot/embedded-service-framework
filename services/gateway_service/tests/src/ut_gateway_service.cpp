#include <exception>
#include <optional>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gateway_service.hpp"

using namespace service;

TEST(ut_gateway_service, run_api_request_sanity) {
	// GIVEN
	MockDataReader data_reader;
	MockDataWriter data_writer;
	MockService service;

	// WHEN:
	TestHost *instance(nullptr);

	THEN:
	ASSERT_NO_THROW(
		instance = new TestHost(
			&data_reader,
			&data_writer,
			&service,
			[](const std::exception& e) -> ApiResponse {
				throw std::runtime_error("NOT IMPLEMENTED");
			}
		)
	);
	
	ASSERT_NO_THROW(delete instance);
	instance = nullptr;
}