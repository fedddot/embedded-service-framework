#ifndef	API_MESSAGE_WRITER_HPP
#define	API_MESSAGE_WRITER_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

#include "data_writer.hpp"
#include "pb.h"
#include "pb_encode.h"

namespace ipc {
	template <typename ApiMessage, typename NanoPbMessage, std::size_t MAX_MSG_SIZE>
	class ApiMessageWriter: public DataWriter<ApiMessage> {
	public:
		using PackageWriter = DataWriter<std::vector<std::uint8_t>>;
		using ApiMessageSerializer = std::function<NanoPbMessage(const ApiMessage&)>;
		ApiMessageWriter(
			PackageWriter *package_writer_ptr,
			const ApiMessageSerializer& message_serializer,
			const pb_msgdesc_t *nanopb_message_fields
		): m_package_writer_ptr(package_writer_ptr), m_message_serializer(message_serializer), m_nanopb_message_fields(nanopb_message_fields) {
			if (!m_package_writer_ptr || !m_message_serializer) {
				throw std::invalid_argument("invalid args received");
			}
		}
		ApiMessageWriter(const ApiMessageWriter&) = default;
		ApiMessageWriter& operator=(const ApiMessageWriter&) = delete;
		void write(const ApiMessage& message) override {
			const auto pb_message = m_message_serializer(message);
			pb_byte_t buff[MAX_MSG_SIZE] = { 0 };
			pb_ostream_t ostream = pb_ostream_from_buffer(
                buff,
                MAX_MSG_SIZE
            );
            if (!pb_encode(&ostream, m_nanopb_message_fields, &pb_message)) {
                throw std::runtime_error("failed to encode api message into protocol buffer: " + std::string(PB_GET_ERROR(&ostream)));
            }
            m_package_writer_ptr->write(std::vector<std::uint8_t>((const char *)buff, (const char *)buff + ostream.bytes_written));
		}
	private:
		PackageWriter *m_package_writer_ptr;
		const ApiMessageSerializer m_message_serializer;
		const pb_msgdesc_t *m_nanopb_message_fields;
	};
}

#endif // API_MESSAGE_WRITER_HPP