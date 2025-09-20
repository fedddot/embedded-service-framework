#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "api_message_reader.hpp"
#include "data_reader.hpp"

using namespace ipc;

using ApiRequest = std::string;

class MockPackageReader : public DataReader<std::optional<std::vector<std::uint8_t>>> {
public:
    MOCK_METHOD(std::optional<std::vector<std::uint8_t>>, read, (), (override));
};

TEST(ut_api_message_reader, ctor_dtor_sanity) {
	// GIVEN
	auto package_reader = MockPackageReader();
	const auto request_parser = [](const std::vector<std::uint8_t>& data) -> ApiRequest {
		throw std::runtime_error("request parser not implemented");
	};

	// WHEN
	ApiMessageReader<ApiRequest> *instance = nullptr;


	// THEN
	ASSERT_NO_THROW(
		instance = new ApiMessageReader<ApiRequest>(
			&package_reader,
			request_parser
		)
	);
	ASSERT_NO_THROW(delete instance);
	instance = nullptr;
}

TEST(ut_api_message_reader, read_sanity) {
	// GIVEN
	const auto test_api_request = ApiRequest("test_msg");
	auto package_reader = ::testing::NiceMock<MockPackageReader>();
    EXPECT_CALL(package_reader, read())
        .WillOnce(::testing::Return(std::vector<std::uint8_t>(test_api_request.begin(), test_api_request.end())));
	const auto request_parser = [](const std::vector<std::uint8_t>& data) -> ApiRequest {
		return ApiRequest(data.begin(), data.end());
	};
	
	// WHEN
	ApiMessageReader<ApiRequest> instance(
		&package_reader,
		request_parser
	);
	auto result = std::optional<ApiRequest>();

	// THEN
	ASSERT_NO_THROW(result = instance.read());
	ASSERT_TRUE(result.has_value());
	ASSERT_EQ(*result, test_api_request);
}