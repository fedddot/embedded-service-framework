#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "package_writer.hpp"
#include "package_utils.hpp"

using namespace ipc;

#define RING_BUFF_SIZE 	0xFFUL
#define HEADER_SIZE 	0x2UL

TEST(ut_package_writer, ctor_dtor_sanity) {
	// GIVEN
	const auto header_generator = [](const std::vector<std::uint8_t>&, const std::size_t&) -> std::vector<std::uint8_t> {
		throw std::runtime_error("header generator not implemented");
	};
	const auto raw_data_writer = [](const std::vector<std::uint8_t>&) {
		throw std::runtime_error("raw data writer not implemented");
	};

	// WHEN
	PackageWriter *instance = nullptr;


	// THEN
	ASSERT_NO_THROW(
		instance = new PackageWriter(
			header_generator,
			raw_data_writer,
			HEADER_SIZE
		)
	);
	ASSERT_NO_THROW(delete instance);
	instance = nullptr;
}

TEST(ut_package_writer, write_sanity) {
	// GIVEN
	auto raw_data_buffer = std::vector<std::uint8_t>();
	const auto header_generator = [](const std::vector<std::uint8_t>& payload, const std::size_t& header_size) -> std::vector<std::uint8_t> {
		return serialize_package_size(payload.size(), header_size);
	};
	const auto raw_data_writer = [&raw_data_buffer](const std::vector<std::uint8_t>& raw_data) {
		raw_data_buffer.insert(raw_data_buffer.end(), raw_data.begin(), raw_data.end());
	};
	
	const auto test_payload_str = std::string("test_payload");
	
	// WHEN
	auto instance = PackageWriter(
		header_generator,
		raw_data_writer,
		HEADER_SIZE
	);

	// THEN
	ASSERT_NO_THROW(instance.write(std::vector<std::uint8_t>(test_payload_str.begin(), test_payload_str.end())));
	ASSERT_EQ(HEADER_SIZE + test_payload_str.size(), raw_data_buffer.size());
}