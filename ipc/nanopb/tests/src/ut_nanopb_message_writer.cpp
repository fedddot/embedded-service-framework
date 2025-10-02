#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nanopb_message_writer.hpp"

using namespace ipc;

using ApiMessage = std::string;

class MockPackageWriter : public DataWriter<std::vector<std::uint8_t>> {
public:
    MOCK_METHOD(void, write, (const std::vector<std::uint8_t>&), (override));
};

TEST(ut_nanopb_message_writer, ctor_dtor_sanity) {
	// GIVEN
	auto package_writer = MockPackageWriter();
	const auto message_serializer = [](const ApiMessage& message) -> std::vector<std::uint8_t> {
		throw std::runtime_error("not implemented");
	};

	// WHEN
	ApiMessageWriter<ApiMessage> *instance = nullptr;


	// THEN
	ASSERT_NO_THROW(
		instance = new ApiMessageWriter<ApiMessage>(
			&package_writer,
			message_serializer
		)
	);
	ASSERT_NO_THROW(delete instance);
	instance = nullptr;
}

TEST(ut_nanopb_message_writer, write_sanity) {
	// GIVEN
	const auto nanopb_message = ApiMessage("test_msg");
	auto package_writer = ::testing::NiceMock<MockPackageWriter>();
    EXPECT_CALL(package_writer, write(::testing::_)).Times(1);
	const auto message_serializer = [](const ApiMessage& message) -> std::vector<std::uint8_t> {
		return std::vector<std::uint8_t>(message.begin(), message.end());
	};

	
	// WHEN
	ApiMessageWriter<ApiMessage> instance(
		&package_writer,
		message_serializer
	);

	// THEN
	ASSERT_NO_THROW(instance.write(nanopb_message));
}