#ifndef	API_MESSAGE_READER_HPP
#define	API_MESSAGE_READER_HPP

#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

#include "data_reader.hpp"

namespace ipc {
	template <typename ApiMessage>
	class ApiMessageReader: public DataReader<std::optional<ApiMessage>> {
	public:
		using PackageReader = DataReader<std::optional<std::vector<std::uint8_t>>>;
		using ApiMessageParser = std::function<ApiMessage(const std::vector<std::uint8_t>&)>;
		ApiMessageReader(
			PackageReader *package_reader_ptr,
			const ApiMessageParser& message_parser
		): m_package_reader_ptr(package_reader_ptr), m_message_parser(message_parser) {
			if (!m_package_reader_ptr || !m_message_parser) {
				throw std::invalid_argument("invalid args received");
			}
		}
		ApiMessageReader(const ApiMessageReader&) = default;
		ApiMessageReader& operator=(const ApiMessageReader&) = delete;
		std::optional<ApiMessage> read() override {
			const auto package_data = m_package_reader_ptr->read();
			if (!package_data) {
				return std::nullopt;
			}
			return m_message_parser(*package_data);
		}
	private:
		PackageReader *m_package_reader_ptr;
		ApiMessageParser m_message_parser;
	};
}

#endif // API_MESSAGE_READER_HPP