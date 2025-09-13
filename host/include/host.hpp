#ifndef	HOST_HPP
#define	HOST_HPP

#include <exception>
#include <functional>
#include <optional>
#include <stdexcept>

#include "data_reader.hpp"
#include "data_writer.hpp"
#include "service.hpp"

namespace host {
	template <typename ApiRequest, typename ApiResponse>
	class Host {
	public:
		using ApiRequestReader = ipc::DataReader<std::optional<ApiRequest>>;
		using ApiResponseWriter = ipc::DataWriter<ApiResponse>;
		using FailureReporter = std::function<ApiResponse(const std::exception&)>;
		using ServiceInstance = service::Service<ApiRequest, ApiResponse>;

		Host(
			ApiRequestReader *api_request_reader_ptr,
			ApiResponseWriter *api_response_writer_ptr,
			ServiceInstance *service_ptr,
			const FailureReporter& failure_reporter
		);
		Host(const Host&) = default;
		Host& operator=(const Host&) = default;
		virtual ~Host() noexcept = default;
		
		void run_once();
	private:
		ApiRequestReader *m_api_request_reader_ptr;
		ApiResponseWriter *m_api_response_writer_ptr;
		ServiceInstance *m_service_ptr;
		FailureReporter m_failure_reporter;
	};

	template <typename ApiRequest, typename ApiResponse>
	inline Host<ApiRequest, ApiResponse>::Host(
			ApiRequestReader *api_request_reader_ptr,
			ApiResponseWriter *api_response_writer_ptr,
			ServiceInstance *service_ptr,
			const FailureReporter& failure_reporter
	): m_api_request_reader_ptr(api_request_reader_ptr), m_api_response_writer_ptr(api_response_writer_ptr), m_service_ptr(service_ptr), m_failure_reporter(failure_reporter) {
		if (!m_api_request_reader_ptr || !m_api_response_writer_ptr || !m_failure_reporter || !m_service_ptr) {
			throw std::invalid_argument("invalid args received in Host ctor");
		}
	}

	template <typename ApiRequest, typename ApiResponse>
	inline void Host<ApiRequest, ApiResponse>::run_once() {
		try {
			const auto request = m_api_request_reader_ptr->read();
			if (!request.has_value()) {
				return;
			}
			const auto response = m_service_ptr->run_api_request(request.value());
			m_api_response_writer_ptr->write(response);
		} catch (const std::exception& e) {
			const auto response = m_failure_reporter(e);
			m_api_response_writer_ptr->write(response);
		}
	}
}

#endif // HOST_HPP