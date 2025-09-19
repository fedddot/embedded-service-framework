#ifndef	API_REQUEST_WRITER_HPP
#define	API_REQUEST_WRITER_HPP

#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

#include "data_writer.hpp"

namespace ipc {
	template <typename ApiResponse>
	class ApiResponseWriter: public DataWriter<ApiResponse> {
	public:
		using PackageWriter = DataWriter<std::vector<std::uint8_t>>;
		using ApiResponseSerializer = std::function<std::vector<std::uint8_t>(const ApiResponse&)>;
		ApiResponseWriter(
			PackageWriter *package_writer_ptr,
			const ApiResponseSerializer& response_serializer
		): m_package_writer_ptr(package_writer_ptr), m_response_serializer(response_serializer) {
			if (!m_package_writer_ptr || !m_response_serializer) {
				throw std::invalid_argument("invalid args received");
			}
		}
		ApiResponseWriter(const ApiResponseWriter&) = default;
		ApiResponseWriter& operator=(const ApiResponseWriter&) = delete;
		void write(const ApiResponse& response) override {
			const auto package_data = m_response_serializer(response);
			m_package_writer_ptr->write(package_data);
		}
	private:
		PackageWriter *m_package_writer_ptr;
		const ApiResponseSerializer m_response_serializer;
	};
}

#endif // API_REQUEST_WRITER_HPP