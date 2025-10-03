#ifndef	MOTOR_DRIVE_SERVICE_API_REQUEST_HPP
#define	MOTOR_DRIVE_SERVICE_API_REQUEST_HPP

#include <functional>

namespace service {
	template <typename RouteId, typename Payload>
	class MotorDriveServiceApiRequest {
	public:
		MotorDriveServiceApiRequest(
			const RouteId& route_id,
			const Payload& payload
		): m_route_id(route_id), m_payload(payload) {}
		MotorDriveServiceApiRequest(const MotorDriveServiceApiRequest&) = default;
		MotorDriveServiceApiRequest& operator=(const MotorDriveServiceApiRequest&) = default;
		virtual ~MotorDriveServiceApiRequest() noexcept = default;
		const RouteId& route_id() const { return std::ref(m_route_id); }
		const Payload& payload() const { return std::ref(m_payload); }
	private:
		RouteId m_route_id;
		Payload m_payload;
	};
}

#endif // MOTOR_DRIVE_SERVICE_API_REQUEST_HPP