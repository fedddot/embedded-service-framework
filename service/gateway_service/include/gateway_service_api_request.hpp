#ifndef	GATEWAY_SERVICE_API_REQUEST_HPP
#define	GATEWAY_SERVICE_API_REQUEST_HPP

#include <functional>

namespace service {
	template <typename RouteId, typename Payload>
	class GatewayServiceApiRequest {
	public:
		GatewayServiceApiRequest(
			const RouteId& route_id,
			const Payload& payload
		): m_route_id(route_id), m_payload(payload) {}
		GatewayServiceApiRequest(const GatewayServiceApiRequest&) = default;
		GatewayServiceApiRequest& operator=(const GatewayServiceApiRequest&) = default;
		virtual ~GatewayServiceApiRequest() noexcept = default;
		const RouteId& route_id() const { return std::ref(m_route_id); }
		const Payload& payload() const { return std::ref(m_payload); }
	private:
		RouteId m_route_id;
		Payload m_payload;
	};
}

#endif // GATEWAY_SERVICE_API_REQUEST_HPP