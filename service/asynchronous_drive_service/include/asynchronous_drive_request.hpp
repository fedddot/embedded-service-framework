#ifndef	ASYNCHRONOUS_DRIVE_REQUEST_HPP
#define	ASYNCHRONOUS_DRIVE_REQUEST_HPP

#include <cstddef>
#include <optional>

namespace service {
	class AsynchronousDriveRequest {
	public:
		enum class Type {
			START,
			GET,
			STOP
		};
		AsynchronousDriveRequest(
			const Type& type,
			const std::optional<std::size_t>& speed_rpm = std::nullopt
		): m_type(type), m_speed_rpm(speed_rpm) {}
		AsynchronousDriveRequest(const AsynchronousDriveRequest&) = default;
		AsynchronousDriveRequest& operator=(const AsynchronousDriveRequest&) = default;
		virtual ~AsynchronousDriveRequest() noexcept = default;

		Type type() const { return m_type; }
		std::optional<std::size_t> speed_rpm() const { return m_speed_rpm; }
	private:
		Type m_type;
		std::optional<std::size_t> m_speed_rpm;
	};
}

#endif // ASYNCHRONOUS_DRIVE_REQUEST_HPP