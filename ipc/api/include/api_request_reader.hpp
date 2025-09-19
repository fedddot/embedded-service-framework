#ifndef	API_REQUEST_READER_HPP
#define	API_REQUEST_READER_HPP

#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

#include "data_reader.hpp"

namespace ipc {
	template <typename ApiRequest>
	class ApiRequestReader: public DataReader<std::optional<ApiRequest>> {
	public:
		using PackageReader = DataReader<std::optional<std::vector<std::uint8_t>>>;
		using ApiRequestParser = std::function<ApiRequest(const std::vector<std::uint8_t>&)>;
		ApiRequestReader(
			PackageReader *package_reader_ptr,
			const ApiRequestParser& request_parser
		): m_package_reader_ptr(package_reader_ptr), m_request_parser(request_parser) {
			if (!m_package_reader_ptr || !m_request_parser) {
				throw std::invalid_argument("invalid args received");
			}
		}
		ApiRequestReader(const ApiRequestReader&) = default;
		ApiRequestReader& operator=(const ApiRequestReader&) = delete;
		std::optional<ApiRequest> read() override {
			const auto package_data = m_package_reader_ptr->read();
			if (!package_data) {
				return std::nullopt;
			}
			return m_request_parser(*package_data);
		}
	private:
		PackageReader *m_package_reader_ptr;
		ApiRequestParser m_request_parser;
	};
}

#endif // API_REQUEST_READER_HPP