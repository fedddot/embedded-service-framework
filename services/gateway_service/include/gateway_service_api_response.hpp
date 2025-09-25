#ifndef	GATEWAY_SERVICE_API_RESPONSE_HPP
#define	GATEWAY_SERVICE_API_RESPONSE_HPP

#include <functional>

#include "gateway_service_types.hpp"

namespace service {
	template <typename RouteId>
	class GatewayServiceApiResponse {
	public:
		GatewayServiceApiResponse(
			const RouteId& route_id,
			const Payload& payload
		): m_route_id(route_id), m_payload(payload) {}
		GatewayServiceApiResponse(const GatewayServiceApiResponse&) = default;
		GatewayServiceApiResponse& operator=(const GatewayServiceApiResponse&) = default;
		virtual ~GatewayServiceApiResponse() noexcept = default;
		const RouteId& route_id() const { return std::ref(m_route_id); }
		const Payload& payload() const { return std::ref(m_payload); }
	private:
		RouteId m_route_id;
		Payload m_payload;
	};
}

#endif // GATEWAY_SERVICE_API_RESPONSE_HPP