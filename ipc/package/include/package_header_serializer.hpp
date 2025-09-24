#ifndef	PACKAGE_HEADER_SERIALIZER_HPP
#define	PACKAGE_HEADER_SERIALIZER_HPP

#include <array>
#include <climits>
#include <cstddef>
#include <cstdint>

#include "package_header.hpp"

namespace ipc {
	template <std::size_t PREAMBLE_SIZE, std::size_t ENCODED_PAYLOAD_SIZE_LENGTH>
	class PackageHeaderSerializer {
	public:
		using RawHeader = std::array<std::uint8_t, PREAMBLE_SIZE + ENCODED_PAYLOAD_SIZE_LENGTH>;
		PackageHeaderSerializer() = default;
		PackageHeaderSerializer(const PackageHeaderSerializer&) = default;
		PackageHeaderSerializer& operator=(const PackageHeaderSerializer&) = default;
		virtual ~PackageHeaderSerializer() noexcept = default;
		RawHeader operator()(const PackageHeader<PREAMBLE_SIZE>& header) const {
			RawHeader raw_header;
			const auto& preamble = header.preamble();
			for (std::size_t i = 0; i < PREAMBLE_SIZE; ++i) {
				raw_header[i] = preamble[i];
			}
			const auto encoded_size = encode_payload_size(header.payload_size());
			for (std::size_t i = PREAMBLE_SIZE; i < PREAMBLE_SIZE + ENCODED_PAYLOAD_SIZE_LENGTH; ++i) {
				raw_header[i] = encoded_size[i - PREAMBLE_SIZE];
			}
			return raw_header;
		}
	private:
		static std::array<std::uint8_t, ENCODED_PAYLOAD_SIZE_LENGTH> encode_payload_size(const std::size_t payload_size) {
			std::array<std::uint8_t, ENCODED_PAYLOAD_SIZE_LENGTH> encoded_size;
			for (std::size_t i = 0; i < ENCODED_PAYLOAD_SIZE_LENGTH; ++i) {
				const auto less_sign_byte = static_cast<char>((payload_size >> CHAR_BIT * i) & 0xFF);
				encoded_size[i] = less_sign_byte;
			}
			return encoded_size;
		}
	};
}

#endif // PACKAGE_HEADER_SERIALIZER_HPP