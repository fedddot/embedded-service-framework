#ifndef	GATEWAY_SERVICE_API_RESPONSE_HPP
#define	GATEWAY_SERVICE_API_RESPONSE_HPP

namespace service {
	class GatewayServiceApiResponse {
	public:
		GatewayServiceApiResponse() = default;
		GatewayServiceApiResponse(const GatewayServiceApiResponse&) = default;
		GatewayServiceApiResponse& operator=(const GatewayServiceApiResponse&) = default;
		virtual ~GatewayServiceApiResponse() noexcept = default;
	private:
		
	};
}

#endif // GATEWAY_SERVICE_API_RESPONSE_HPP