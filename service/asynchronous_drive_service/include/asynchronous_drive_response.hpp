#ifndef	ASYNCHRONOUS_DRIVE_RESPONSE_HPP
#define	ASYNCHRONOUS_DRIVE_RESPONSE_HPP

#include <cstddef>
#include <optional>

namespace service {
	class AsynchronousDriveResponse {
	public:
		enum class Result {
			SUCCESS,
			FAILURE,
		};
		AsynchronousDriveResponse(
			const Result& result,
			const std::optional<std::size_t>& speed_rpm = std::nullopt
		): m_result(result), m_speed_rpm(speed_rpm) {}
		AsynchronousDriveResponse(const AsynchronousDriveResponse&) = default;
		AsynchronousDriveResponse& operator=(const AsynchronousDriveResponse&) = default;
		virtual ~AsynchronousDriveResponse() noexcept = default;

		Result result() const { return m_result; }
		std::optional<std::size_t> speed_rpm() const { return m_speed_rpm; }
	private:
		Result m_result;
		std::optional<std::size_t> m_speed_rpm;
	};
}

#endif // ASYNCHRONOUS_DRIVE_RESPONSE_HPP