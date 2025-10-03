#ifndef	MOTOR_DRIVE_SERVICE_API_REQUEST_HPP
#define	MOTOR_DRIVE_SERVICE_API_REQUEST_HPP

#include <functional>
#include <optional>

namespace service {
	class MotorDriveServiceApiRequest {
	public:
		enum class Type: int {
			START,
			STOP,
			STATUS
		};
		MotorDriveServiceApiRequest(
			const Type& type,
			const std::optional<double>& speed
		): m_type(type), m_speed(speed) {}
		MotorDriveServiceApiRequest(const MotorDriveServiceApiRequest&) = default;
		MotorDriveServiceApiRequest& operator=(const MotorDriveServiceApiRequest&) = default;
		virtual ~MotorDriveServiceApiRequest() noexcept = default;
		const Type& type() const { return std::ref(m_type); }
		const std::optional<double>& speed() const { return std::ref(m_speed); }
	private:
		Type m_type;
		std::optional<double> m_speed;
	};
}

#endif // MOTOR_DRIVE_SERVICE_API_REQUEST_HPP