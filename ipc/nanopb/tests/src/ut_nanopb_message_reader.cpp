#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nanopb_message_reader.hpp"
#include "data_reader.hpp"

using namespace ipc;

using ApiMessage = std::string;

class MockPackageReader : public DataReader<std::optional<std::vector<std::uint8_t>>> {
public:
    MOCK_METHOD(std::optional<std::vector<std::uint8_t>>, read, (), (override));
};

TEST(ut_nanopb_message_reader, ctor_dtor_sanity) {
	// GIVEN
	auto package_reader = MockPackageReader();
	const auto message_parser = [](const std::vector<std::uint8_t>& data) -> ApiMessage {
		throw std::runtime_error("message parser not implemented");
	};

	// WHEN
	ApiMessageReader<ApiMessage> *instance = nullptr;


	// THEN
	ASSERT_NO_THROW(
		instance = new ApiMessageReader<ApiMessage>(
			&package_reader,
			message_parser
		)
	);
	ASSERT_NO_THROW(delete instance);
	instance = nullptr;
}

TEST(ut_nanopb_message_reader, read_sanity) {
	// GIVEN
	const auto test_nanopb_message = ApiMessage("test_msg");
	auto package_reader = ::testing::NiceMock<MockPackageReader>();
    EXPECT_CALL(package_reader, read())
        .WillOnce(::testing::Return(std::vector<std::uint8_t>(test_nanopb_message.begin(), test_nanopb_message.end())));
	const auto message_parser = [](const std::vector<std::uint8_t>& data) -> ApiMessage {
		return ApiMessage(data.begin(), data.end());
	};
	
	// WHEN
	ApiMessageReader<ApiMessage> instance(
		&package_reader,
		message_parser
	);
	auto result = std::optional<ApiMessage>();

	// THEN
	ASSERT_NO_THROW(result = instance.read());
	ASSERT_TRUE(result.has_value());
	ASSERT_EQ(*result, test_nanopb_message);
}