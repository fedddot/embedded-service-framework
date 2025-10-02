#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nanopb_message_reader.hpp"
#include "data_reader.hpp"
#include "test.pb.h"

using namespace ipc;

using ApiMessage = std::string;

class MockPackageReader : public DataReader<std::optional<std::vector<std::uint8_t>>> {
public:
    MOCK_METHOD(std::optional<std::vector<std::uint8_t>>, read, (), (override));
};

TEST(ut_nanopb_message_reader, read_sanity) {
	// GIVEN
	const auto test_nanopb_message = ApiMessage("test_msg");
	const test_api_TestRequest pb_message = test_api_TestRequest_init_default;
	auto package_reader = ::testing::NiceMock<MockPackageReader>();
    EXPECT_CALL(package_reader, read())
        .WillOnce(::testing::Return(std::vector<std::uint8_t>(test_nanopb_message.begin(), test_nanopb_message.end())));
	const auto message_parser = [](const std::vector<std::uint8_t>& data) -> ApiMessage {
		return ApiMessage(data.begin(), data.end());
	};
	
	// WHEN
	NanopbMessageReader<ApiMessage, test_api_TestRequest> instance(
		&package_reader,
		message_parser
	);
	auto result = std::optional<ApiMessage>();

	// THEN
	ASSERT_NO_THROW(result = instance.read());
	ASSERT_TRUE(result.has_value());
	ASSERT_EQ(*result, test_nanopb_message);
}