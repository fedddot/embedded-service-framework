#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "api_response_writer.hpp"

using namespace ipc;

using ApiResponse = std::string;

class MockPackageWriter : public DataWriter<std::vector<std::uint8_t>> {
public:
    MOCK_METHOD(void, write, (const std::vector<std::uint8_t>&), (override));
};

TEST(ut_api_response_writer, ctor_dtor_sanity) {
	// GIVEN
	auto package_writer = MockPackageWriter();
	const auto response_serializer = [](const ApiResponse& response) -> std::vector<std::uint8_t> {
		throw std::runtime_error("not implemented");
	};

	// WHEN
	ApiResponseWriter<ApiResponse> *instance = nullptr;


	// THEN
	ASSERT_NO_THROW(
		instance = new ApiResponseWriter<ApiResponse>(
			&package_writer,
			response_serializer
		)
	);
	ASSERT_NO_THROW(delete instance);
	instance = nullptr;
}

TEST(ut_api_response_writer, write_sanity) {
	// GIVEN
	const auto api_response = ApiResponse("test_msg");
	auto package_writer = ::testing::NiceMock<MockPackageWriter>();
    EXPECT_CALL(package_writer, write(::testing::_)).Times(1);
	const auto response_serializer = [](const ApiResponse& response) -> std::vector<std::uint8_t> {
		return std::vector<std::uint8_t>(response.begin(), response.end());
	};

	
	// WHEN
	ApiResponseWriter<ApiResponse> instance(
		&package_writer,
		response_serializer
	);

	// THEN
	ASSERT_NO_THROW(instance.write(api_response));
}