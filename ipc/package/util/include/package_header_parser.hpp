#ifndef	PACKAGE_HEADER_PARSER
#define	PACKAGE_HEADER_PARSER

#include <array>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "package_header.hpp"

namespace ipc {
	template <std::size_t PREAMBLE_SIZE, std::size_t ENCODED_PAYLOAD_SIZE_LENGTH>
	class PackageHeaderParser {
	public:
		using RawHeader = std::array<std::uint8_t, PREAMBLE_SIZE + ENCODED_PAYLOAD_SIZE_LENGTH>;
		PackageHeaderParser() = default;
		PackageHeaderParser(const PackageHeaderParser&) = default;
		PackageHeaderParser& operator=(const PackageHeaderParser&) = default;
		virtual ~PackageHeaderParser() noexcept = default;
		PackageHeader<PREAMBLE_SIZE> operator()(const RawHeader& raw_header) const {
			if (PREAMBLE_SIZE + ENCODED_PAYLOAD_SIZE_LENGTH != raw_header.size()) {
				throw std::invalid_argument("invalid raw header size received");
			}
			typename PackageHeader<PREAMBLE_SIZE>::Preamble preamble;
			for (std::size_t i = 0; i < PREAMBLE_SIZE; ++i) {
				preamble[i] = raw_header[i];
			}
			std::array<std::uint8_t, ENCODED_PAYLOAD_SIZE_LENGTH> package_size_data;
			for (std::size_t i = 0; i < ENCODED_PAYLOAD_SIZE_LENGTH; ++i) {
				package_size_data[i] = raw_header[i + PREAMBLE_SIZE];
			}
			return PackageHeader<PREAMBLE_SIZE>(preamble, decode_package_size(package_size_data));
		}
	private:
		static std::size_t decode_package_size(const std::array<std::uint8_t, ENCODED_PAYLOAD_SIZE_LENGTH>& package_size_data) {
			if (sizeof(std::size_t) < ENCODED_PAYLOAD_SIZE_LENGTH) {
				throw std::invalid_argument("invalid raw data size");
			}
			auto decoded_size = std::size_t(0UL);
			for (std::size_t i = 0; i < ENCODED_PAYLOAD_SIZE_LENGTH; ++i) {
				decoded_size <<= CHAR_BIT;
				decoded_size |= static_cast<std::size_t>(package_size_data[ENCODED_PAYLOAD_SIZE_LENGTH - 1 - i]);
			}
			return decoded_size;
		}
	};
}

#endif // PACKAGE_HEADER_PARSER