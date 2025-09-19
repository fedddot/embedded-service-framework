#ifndef	PACKAGE_READER_HPP
#define	PACKAGE_READER_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

#include "input_stream.hpp"
#include "data_reader.hpp"

namespace ipc {
	class PackageReader: public DataReader<std::optional<std::vector<std::uint8_t>>> {
	public:
		using SizeRetriever = std::function<std::size_t(const InputStream<std::uint8_t>&)>;
		PackageReader(
			InputStream<std::uint8_t> *queue_ptr,
			const SizeRetriever& size_retriever,
			const std::size_t& header_size
		);
		PackageReader(const PackageReader&) = default;
		PackageReader& operator=(const PackageReader&) = delete;
		std::optional<std::vector<std::uint8_t>> read() override;
	private:
		InputStream<std::uint8_t> *m_queue_ptr;
		SizeRetriever m_size_retriever;
		std::size_t m_header_size;
	};

	inline PackageReader::PackageReader(
		InputStream<std::uint8_t> *queue_ptr,
		const SizeRetriever& size_retriever,
		const std::size_t& header_size
	): m_queue_ptr(queue_ptr), m_size_retriever(size_retriever), m_header_size(header_size) {
		if (!m_queue_ptr || !m_size_retriever) {
			throw std::invalid_argument("invalid args in package reader received");
		}
	}

	inline std::optional<std::vector<std::uint8_t>> PackageReader::read() {
		try {
			if (m_queue_ptr->size() < m_header_size) {
				return std::nullopt;
			}
			const auto package_size = m_size_retriever(*m_queue_ptr);
			if (m_queue_ptr->size() < package_size + m_header_size) {
				return std::nullopt;
			}
			std::vector<std::uint8_t> package_data(package_size, 0);
			for (std::size_t i = 0; i < package_size; ++i) {
				package_data[i] = m_queue_ptr->inspect(i + m_header_size);
			}
			auto bytes_to_discard = m_header_size + package_size;
			while (bytes_to_discard) {
				m_queue_ptr->read();
				--bytes_to_discard;
			}
			return package_data;
		} catch (...) {
			m_queue_ptr->clear();
			throw;
		}
	}
}

#endif // PACKAGE_READER_HPP