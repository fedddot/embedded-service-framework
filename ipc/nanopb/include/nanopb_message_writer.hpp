#ifndef	API_MESSAGE_WRITER_HPP
#define	API_MESSAGE_WRITER_HPP

#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

#include "data_writer.hpp"

namespace ipc {
	template <typename ApiMessage>
	class ApiMessageWriter: public DataWriter<ApiMessage> {
	public:
		using PackageWriter = DataWriter<std::vector<std::uint8_t>>;
		using ApiMessageSerializer = std::function<std::vector<std::uint8_t>(const ApiMessage&)>;
		ApiMessageWriter(
			PackageWriter *package_writer_ptr,
			const ApiMessageSerializer& message_serializer
		): m_package_writer_ptr(package_writer_ptr), m_message_serializer(message_serializer) {
			if (!m_package_writer_ptr || !m_message_serializer) {
				throw std::invalid_argument("invalid args received");
			}
		}
		ApiMessageWriter(const ApiMessageWriter&) = default;
		ApiMessageWriter& operator=(const ApiMessageWriter&) = delete;
		void write(const ApiMessage& message) override {
			throw std::runtime_error("NOT IMPLEMENTED");
		}
	private:
		PackageWriter *m_package_writer_ptr;
		const ApiMessageSerializer m_message_serializer;
	};
}

#endif // API_MESSAGE_WRITER_HPP