#ifndef	GATEWAY_SERVICE_API_REQUEST_HPP
#define	GATEWAY_SERVICE_API_REQUEST_HPP

namespace service {
	class GatewayServiceApiRequest {
	public:
		GatewayServiceApiRequest() = default;
		GatewayServiceApiRequest(const GatewayServiceApiRequest&) = default;
		GatewayServiceApiRequest& operator=(const GatewayServiceApiRequest&) = default;
		virtual ~GatewayServiceApiRequest() noexcept = default;
	private:
		
	};
}

#endif // GATEWAY_SERVICE_API_REQUEST_HPP