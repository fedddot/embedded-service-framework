#ifndef	CNC_SERVICE_API_RESPONSE_HPP
#define	CNC_SERVICE_API_RESPONSE_HPP

#include <functional>
#include <optional>
#include <string>

namespace service {
	class CncServiceApiResponse {
	public:
		enum class Result: int {
			SUCCESS = 0,
			BAD_REQUEST = 1,
			UNEXPECTED_FAILURE = 2,
		};
		CncServiceApiResponse(
			const Result& result,
			const std::optional<std::string>& message = std::nullopt
		): m_result(result), m_message(message) {}
		CncServiceApiResponse(const CncServiceApiResponse&) = default;
		CncServiceApiResponse& operator=(const CncServiceApiResponse&) = default;
		virtual ~CncServiceApiResponse() noexcept = default;
		const Result& result() const { return std::ref(m_result); }
		const std::optional<std::string>& message() const { return std::ref(m_message); }
	private:
		Result m_result;
		std::optional<std::string> m_message;
	};
}

#endif // CNC_SERVICE_API_RESPONSE_HPP