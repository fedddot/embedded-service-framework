#ifndef	RAW_DATA_PACKAGE_WRITER_HPP
#define	RAW_DATA_PACKAGE_WRITER_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

#include "data_writer.hpp"
#include "package_header.hpp"

namespace ipc {
	template <std::size_t PREAMBLE_SIZE, std::size_t ENCODED_PAYLOAD_SIZE_LENGTH>
	class PackageWriter: public DataWriter<std::vector<std::uint8_t>> {
	public:
		using Preamble = typename PackageHeader<PREAMBLE_SIZE>::Preamble;
		using RawHeader = std::array<std::uint8_t, PREAMBLE_SIZE + ENCODED_PAYLOAD_SIZE_LENGTH>;
		using HeaderSerializer = std::function<RawHeader(const PackageHeader<PREAMBLE_SIZE>&)>;
		using RawDataWriter = std::function<void(const std::vector<std::uint8_t>&)>;
		PackageWriter(
			const RawDataWriter& raw_data_writer,
			const Preamble& preamble,
			const HeaderSerializer& header_serializer
		): m_raw_data_writer(raw_data_writer), m_preamble(preamble), m_header_serializer(header_serializer) {
			if (!m_raw_data_writer || !m_header_serializer) {
				throw std::invalid_argument("invalid args in package writer received");
			}
		}
		PackageWriter(const PackageWriter&) = default;
		PackageWriter& operator=(const PackageWriter&) = delete;
		void write(const std::vector<std::uint8_t>& payload) override {
			const auto header = PackageHeader<PREAMBLE_SIZE>(m_preamble, payload.size());
			const auto header_encoded = m_header_serializer(header);
			const auto header_size = header_encoded.size();
			std::vector<std::uint8_t> raw_data(header_size + payload.size(), 0);
			for (auto i = 0; i < header_size; ++i) {
				raw_data[i] = header_encoded[i];
			}
			for (auto i = header_size; i < header_size + payload.size(); ++i) {
				raw_data[i] = payload[i - header_size];
			}
			m_raw_data_writer(raw_data);
		}
	private:
		RawDataWriter m_raw_data_writer;
		Preamble m_preamble;
		HeaderSerializer m_header_serializer;
	};
}

#endif // RAW_DATA_PACKAGE_WRITER_HPP