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
			const ApiMessageSerializer& response_serializer
		): m_package_writer_ptr(package_writer_ptr), m_response_serializer(response_serializer) {
			if (!m_package_writer_ptr || !m_response_serializer) {
				throw std::invalid_argument("invalid args received");
			}
		}
		ApiMessageWriter(const ApiMessageWriter&) = default;
		ApiMessageWriter& operator=(const ApiMessageWriter&) = delete;
		void write(const ApiMessage& response) override {
			const auto package_data = m_response_serializer(response);
			m_package_writer_ptr->write(package_data);
		}
	private:
		PackageWriter *m_package_writer_ptr;
		const ApiMessageSerializer m_response_serializer;
	};
}

#endif // API_MESSAGE_WRITER_HPP