#ifndef	GATEWAY_SERVICE_HPP
#define	GATEWAY_SERVICE_HPP

#include <functional>
#include <stdexcept>
#include <unordered_map>

#include "gateway_service_api_request.hpp"
#include "gateway_service_api_response.hpp"
#include "service.hpp"

namespace service {
	template <typename RouteId, typename Payload>
	class GatewayService: public Service<GatewayServiceApiRequest<RouteId, Payload>, GatewayServiceApiResponse<RouteId, Payload>> {
	public:
		using ApiRequestHandler = std::function<Payload(const Payload& request_payload)>;
		GatewayService() = default;
		GatewayService(const GatewayService&) = delete;
		GatewayService& operator=(const GatewayService&) = delete;
		GatewayServiceApiResponse<RouteId, Payload> run_api_request(const GatewayServiceApiRequest<RouteId, Payload>& request) override {
			const auto handler_iter = m_route_handlers.find(request.route_id());
			if (m_route_handlers.end() == handler_iter) {
				throw std::invalid_argument("no handler registered for received route id");
			}
			const auto handler_response_payload = handler_iter->second(request.payload());
			return GatewayServiceApiResponse<RouteId, Payload>(request.route_id(), handler_response_payload);
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

#endif // GATEWAY_SERVICE_HPP