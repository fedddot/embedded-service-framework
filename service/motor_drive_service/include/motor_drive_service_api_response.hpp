#ifndef	MOTOR_DRIVE_SERVICE_API_RESPONSE_HPP
#define	MOTOR_DRIVE_SERVICE_API_RESPONSE_HPP

#include <functional>
#include <optional>

namespace service {
	template <typename RouteId, typename Payload>
	class MotorDriveServiceApiResponse {
	public:
		enum class Result: int {
			SUCCESS = 0,
			UNSUPPORTED_ROUTE = 1,
			UNEXPECTED_FAILURE = 2
		};
		MotorDriveServiceApiResponse(
			const Result& result,
			const RouteId& route_id,
			const std::optional<Payload>& payload
		): m_result(result), m_route_id(route_id), m_payload(payload) {}
		MotorDriveServiceApiResponse(const MotorDriveServiceApiResponse&) = default;
		MotorDriveServiceApiResponse& operator=(const MotorDriveServiceApiResponse&) = default;
		virtual ~MotorDriveServiceApiResponse() noexcept = default;
		const Result& result() const { return std::ref(m_result); }
		const RouteId& route_id() const { return std::ref(m_route_id); }
		const std::optional<Payload>& payload() const { return std::ref(m_payload); }
	private:
		Result m_result;
		RouteId m_route_id;
		std::optional<Payload> m_payload;
	};
}

#endif // MOTOR_DRIVE_SERVICE_API_RESPONSE_HPP