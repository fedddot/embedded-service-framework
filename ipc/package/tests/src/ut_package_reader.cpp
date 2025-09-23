#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "package_reader.hpp"
#include "package_header_parser.hpp"
#include "package_header_serializer.hpp"
#include "ring_buffer_input_stream.hpp"

using namespace ipc;

#define RING_BUFF_SIZE 	0xFFUL
#define PREAMBLE_SIZE	0x04UL
#define ENCODED_PAYLOAD_SIZE_LENGTH 0x02UL

using TestPackageReader = PackageReader<PREAMBLE_SIZE, ENCODED_PAYLOAD_SIZE_LENGTH>;

TEST(ut_package_reader, read_sanity) {
	// GIVEN
	const std::string payload_str("test_msg");
	const TestPackageReader::Preamble preamble = {0xDE, 0xAD, 0xBE, 0xEF};
	const auto msg_header = PackageHeader<PREAMBLE_SIZE>(preamble, payload_str.size());
	const auto msg_header_encoded = PackageHeaderSerializer<PREAMBLE_SIZE, ENCODED_PAYLOAD_SIZE_LENGTH>()(msg_header);

	// WHEN
	RingBufferInputStream<std::uint8_t, RING_BUFF_SIZE> buff;
	TestPackageReader instance(
		&buff,
		preamble,
		PackageHeaderParser<PREAMBLE_SIZE, ENCODED_PAYLOAD_SIZE_LENGTH>()
	);
	auto result = std::optional<std::vector<std::uint8_t>>();

	// THEN
	// empty buffer
	ASSERT_NO_THROW(result = instance.read());
	ASSERT_FALSE(result);

	// add encoded message size
	for (const auto& byte: msg_header_encoded) {
		buff.enqueue(byte);
	}
	ASSERT_NO_THROW(result = instance.read());
	ASSERT_FALSE(result);
	
	// add message
	for (const auto& byte: payload_str) {
		buff.enqueue(static_cast<std::uint8_t>(byte));
	}
	ASSERT_NO_THROW(result = instance.read());
	ASSERT_TRUE(result);
	ASSERT_EQ(payload_str, std::string(result->begin(), result->end()));
	ASSERT_EQ(0UL, buff.size());
}