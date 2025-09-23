#ifndef	PACKAGE_READER_HPP
#define	PACKAGE_READER_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

#include "input_stream.hpp"
#include "data_reader.hpp"
#include "package_header.hpp"

namespace ipc {
	/// @brief Reads data packages from a byte stream.
	/// @details A package has the following structure:
	///	[fixed-size header][payload]
	/// Where:
	///		- [fixed-size header] starts with a preamble and contains encoded payload size: [<preamble><encoded payload size>]
	///		- [payload] data of size corresponding to the encoded payload size
	template <std::size_t PREAMBLE_SIZE, std::size_t ENCODED_PAYLOAD_SIZE_LENGTH>
	class PackageReader: public DataReader<std::optional<std::vector<std::uint8_t>>> {
	public:
		using Preamble = typename PackageHeader<PREAMBLE_SIZE>::Preamble;
		using RawHeader = std::array<std::uint8_t, PREAMBLE_SIZE + ENCODED_PAYLOAD_SIZE_LENGTH>;
		using HeaderParser = std::function<PackageHeader<PREAMBLE_SIZE>(const RawHeader&)>;
		PackageReader(
			InputStream<std::uint8_t> *byte_stream_ptr,
			const Preamble& preamble,
			const HeaderParser& header_parser
		): m_byte_stream_ptr(byte_stream_ptr), m_preamble(preamble), m_header_parser(header_parser) {
			if (!m_byte_stream_ptr || !m_header_parser) {
				throw std::invalid_argument("invalid args received in package reader");
			}
		}
		PackageReader(const PackageReader&) = default;
		PackageReader& operator=(const PackageReader&) = delete;
		std::optional<std::vector<std::uint8_t>> read() override {
			const auto header_size = PREAMBLE_SIZE + ENCODED_PAYLOAD_SIZE_LENGTH;
			if (m_byte_stream_ptr->size() < header_size) {
				return std::nullopt;
			}
			RawHeader raw_header;
			for (std::size_t i = 0; i < header_size; ++i) {
				raw_header[i] = m_byte_stream_ptr->inspect(i);
			}
			const auto header = m_header_parser(raw_header);
			if (header.preamble() != m_preamble) {
				m_byte_stream_ptr->clear();
				throw std::runtime_error("invalid preamble in package reader");
			}
			const auto package_size = header.payload_size();
			if (m_byte_stream_ptr->size() < package_size + header_size) {
				return std::nullopt;
			}
			std::vector<std::uint8_t> package_data(package_size, 0);
			for (std::size_t i = 0; i < package_size; ++i) {
				package_data[i] = m_byte_stream_ptr->inspect(i + header_size);
			}
			auto bytes_to_discard = header_size + package_size;
			while (bytes_to_discard) {
				m_byte_stream_ptr->read();
				--bytes_to_discard;
			}
			return package_data;
		}
	private:
		InputStream<std::uint8_t> *m_byte_stream_ptr;
		Preamble m_preamble;
		HeaderParser m_header_parser;
	};
}

#endif // PACKAGE_READER_HPP