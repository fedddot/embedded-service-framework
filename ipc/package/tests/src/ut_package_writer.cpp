#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "package_writer.hpp"
#include "package_header_serializer.hpp"

using namespace ipc;

#define RING_BUFF_SIZE 	0xFFUL
#define PREAMBLE_SIZE	0x04UL
#define ENCODED_PAYLOAD_SIZE_LENGTH 0x02UL

using TestPackageWriter = PackageWriter<PREAMBLE_SIZE, ENCODED_PAYLOAD_SIZE_LENGTH>;

TEST(ut_package_writer, write_sanity) {
	// GIVEN
	const std::string payload_str("test_msg");
	const TestPackageWriter::Preamble preamble = {0xDE, 0xAD, 0xBE, 0xEF};
	const auto msg_header = PackageHeader<PREAMBLE_SIZE>(preamble, payload_str.size());
	const auto msg_header_encoded = PackageHeaderSerializer<PREAMBLE_SIZE, ENCODED_PAYLOAD_SIZE_LENGTH>()(msg_header);
	
	// WHEN
	TestPackageWriter instance(
		[msg_header_encoded, payload_str](const std::vector<std::uint8_t>& raw_data) {
			// THEN: validate the header:
			for (auto i = 0; i < msg_header_encoded.size(); ++i) {
				ASSERT_EQ(raw_data[i], msg_header_encoded[i]);
			}
			// THEN: validate the payload:
			for (auto i = msg_header_encoded.size(); i < raw_data.size(); ++i) {
				ASSERT_EQ(raw_data[i], payload_str[i - msg_header_encoded.size()]);
			}
		},
		preamble,
		PackageHeaderSerializer<PREAMBLE_SIZE, ENCODED_PAYLOAD_SIZE_LENGTH>()
	);

	// THEN
	ASSERT_NO_THROW(instance.write(std::vector<std::uint8_t>(payload_str.begin(), payload_str.end())));
}