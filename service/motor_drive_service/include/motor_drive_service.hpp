#ifndef	MOTOR_DRIVE_SERVICE_HPP
#define	MOTOR_DRIVE_SERVICE_HPP

#include <functional>
#include <optional>
#include <stdexcept>
#include <unordered_map>

#include "motor_drive_service_api_request.hpp"
#include "motor_drive_service_api_response.hpp"
#include "service.hpp"

namespace service {
	template <typename RouteId, typename Payload>
	class MotorDriveService: public Service<MotorDriveServiceApiRequest<RouteId, Payload>, MotorDriveServiceApiResponse<RouteId, Payload>> {
	public:
		using ApiRequestHandler = std::function<std::optional<Payload>(const Payload& request_payload)>;
		MotorDriveService() = default;
		MotorDriveService(const MotorDriveService&) = delete;
		MotorDriveService& operator=(const MotorDriveService&) = delete;
		MotorDriveServiceApiResponse<RouteId, Payload> run_api_request(const MotorDriveServiceApiRequest<RouteId, Payload>& request) override {
			const auto handler_iter = m_route_handlers.find(request.route_id());
			if (m_route_handlers.end() == handler_iter) {
				return MotorDriveServiceApiResponse<RouteId, Payload>(
					MotorDriveServiceApiResponse<RouteId, Payload>::Result::UNSUPPORTED_ROUTE,
					request.route_id(),
					std::nullopt
				);
			}
			try {
				const auto handler_response = handler_iter->second(request.payload());
				return MotorDriveServiceApiResponse<RouteId, Payload>(
					MotorDriveServiceApiResponse<RouteId, Payload>::Result::SUCCESS,
					request.route_id(),
					handler_response
				);
			} catch (...) {
				return MotorDriveServiceApiResponse<RouteId, Payload>(
					MotorDriveServiceApiResponse<RouteId, Payload>::Result::UNEXPECTED_FAILURE,
					request.route_id(),
					std::nullopt
				);
			}
		}
		void register_route_handler(const RouteId& route_id, const ApiRequestHandler& handler) {
			if (!handler) {
				throw std::invalid_argument("invalid handler received");
			}
			m_route_handlers[route_id] = handler;
		}
	private:
		std::unordered_map<RouteId, ApiRequestHandler> m_route_handlers;
	};
}

#endif // MOTOR_DRIVE_SERVICE_HPP