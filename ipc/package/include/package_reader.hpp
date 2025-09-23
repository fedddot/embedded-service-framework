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
		using Preamble = std::array<std::uint8_t, PREAMBLE_SIZE>;
		using EncodedPayloadSize = std::array<std::uint8_t, ENCODED_PAYLOAD_SIZE_LENGTH>;
		using SizeRetriever = std::function<std::size_t(const InputStream<std::uint8_t>&)>;
		PackageReader(
			InputStream<std::uint8_t> *byte_stream_ptr,
			const std::array<typename Tp, size_t Nm><std::uint8_t>& preamble,
			const std::size_t encoded_payload_size_length,
			const SizeRetriever& size_retriever
		);
		PackageReader(const PackageReader&) = default;
		PackageReader& operator=(const PackageReader&) = delete;
		std::optional<std::vector<std::uint8_t>> read() override;
	private:
		InputStream<std::uint8_t> *m_byte_stream_ptr;
		SizeRetriever m_size_retriever;
		std::size_t m_header_size;
	};

	inline PackageReader::PackageReader(
		InputStream<std::uint8_t> *byte_stream_ptr,
		const SizeRetriever& size_retriever,
		const std::size_t& header_size
	): m_byte_stream_ptr(byte_stream_ptr), m_size_retriever(size_retriever), m_header_size(header_size) {
		if (!m_byte_stream_ptr || !m_size_retriever) {
			throw std::invalid_argument("invalid args in package reader received");
		}
	}

	inline std::optional<std::vector<std::uint8_t>> PackageReader::read() {
		try {
			if (m_byte_stream_ptr->size() < m_header_size) {
				return std::nullopt;
			}
			const auto package_size = m_size_retriever(*m_byte_stream_ptr);
			if (m_byte_stream_ptr->size() < package_size + m_header_size) {
				return std::nullopt;
			}
			std::vector<std::uint8_t> package_data(package_size, 0);
			for (std::size_t i = 0; i < package_size; ++i) {
				package_data[i] = m_byte_stream_ptr->inspect(i + m_header_size);
			}
			auto bytes_to_discard = m_header_size + package_size;
			while (bytes_to_discard) {
				m_byte_stream_ptr->read();
				--bytes_to_discard;
			}
			return package_data;
		} catch (...) {
			m_byte_stream_ptr->clear();
			throw;
		}
	}
}

#endif // PACKAGE_READER_HPP