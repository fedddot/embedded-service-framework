#include <exception>
#include <optional>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "host.hpp"
#include "service.hpp"
#include "data_reader.hpp"
#include "data_writer.hpp"

using namespace service;
using namespace host;
using namespace ipc;

using ApiRequest = std::string;
using ApiResponse = int;
using TestHost = Host<ApiRequest, ApiResponse>;

class MockDataReader : public TestHost::ApiRequestReader {
public:
    MOCK_METHOD(std::optional<ApiRequest>, read, (), (override));
};

class MockDataWriter : public TestHost::ApiResponseWriter {
public:
    MOCK_METHOD(void, write, (const ApiResponse&), (override));
};

class MockService : public Service<ApiRequest, ApiResponse> {
public:
    MOCK_METHOD(ApiResponse, run_api_request, (const ApiRequest&), (override));
};

TEST(ut_host, ctor_dtor_sanity) {
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

TEST(ut_host, run_once_sanity) {
	// GIVEN
	const auto test_api_request = ApiRequest("test_request");
	const auto test_api_response = ApiResponse(12);
	const auto data_reader = TestDataReader<std::optional<ApiRequest>(void)>(
		[test_api_request](void) -> std::optional<ApiRequest> {
			return test_api_request;
		}
	);
	const auto data_writer = TestIpcDataWriter<ApiResponse>(
		[test_api_response](const ApiResponse& response){
			ASSERT_EQ(test_api_response, response);
		}
	);
	auto service = TestService<ApiRequest, ApiResponse>(
		[test_api_response](const ApiRequest&) -> ApiResponse {
			return ApiResponse(test_api_response);
		}
	);

	// WHEN:
	TestHost instance(
		&data_reader,
		&data_writer,
		[](const std::exception& e) -> ApiResponse {
			throw std::runtime_error("NOT IMPLEMENTED");
		},
		&service
	);

	// THEN:
	ASSERT_NO_THROW(instance.run_once());
}