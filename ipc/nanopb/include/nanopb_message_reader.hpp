#ifndef	API_MESSAGE_READER_HPP
#define	API_MESSAGE_READER_HPP

#include <cstdint>
#include <cstring>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

#include "pb_decode.h"

#include "data_reader.hpp"

namespace ipc {
	template <typename ApiMessage, typename NanoPbMessage>
	class ApiMessageReader: public DataReader<std::optional<ApiMessage>> {
	public:
		using PackageReader = DataReader<std::optional<std::vector<std::uint8_t>>>;
		using ApiMessageParser = std::function<ApiMessage(const NanoPbMessage&)>;
		ApiMessageReader(
			PackageReader *package_reader_ptr,
			const ApiMessageParser& message_parser,
			const NanoPbMessage& init_nanopb_message,
			const pb_msgdesc_t& nanopb_message_fields
		): m_package_reader_ptr(package_reader_ptr), m_message_parser(message_parser), m_init_nanopb_message(init_nanopb_message), m_nanopb_message_fields(nanopb_message_fields) {
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
			const auto stream = pb_istream_from_buffer((*package_data).data(), (*package_data).size());
			NanoPbMessage request(m_init_nanopb_message);
			if (!pb_decode(&stream, &m_nanopb_message_fields, &request)) {
                throw std::runtime_error("failed to decode Nano PB request: " + std::string(PB_GET_ERROR(&stream)));
            }
			return m_message_parser(request);
		}
	private:
		PackageReader *m_package_reader_ptr;
		ApiMessageParser m_message_parser;
		NanoPbMessage m_init_nanopb_message;
		pb_msgdesc_t m_nanopb_message_fields;
	};
}

#endif // API_MESSAGE_READER_HPP