#include <exception>
#include <optional>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "host.hpp"

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

class MockService : public TestHost::Service {
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

    auto data_reader = ::testing::NiceMock<MockDataReader>();
    auto data_writer = ::testing::NiceMock<MockDataWriter>();
    auto service = ::testing::NiceMock<MockService>();

    EXPECT_CALL(data_reader, read())
        .WillOnce(::testing::Return(test_api_request));
    EXPECT_CALL(service, run_api_request(test_api_request))
        .WillOnce(::testing::Return(test_api_response));
    EXPECT_CALL(data_writer, write(test_api_response))
        .Times(1);

    TestHost instance(
        &data_reader,
        &data_writer,
        &service,
        [](const std::exception& e) -> ApiResponse {
            throw std::runtime_error("NOT IMPLEMENTED");
        }
    );

    // THEN:
    ASSERT_NO_THROW(instance.run_once());
}