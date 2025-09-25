#ifndef	GATEWAY_SERVICE_HPP
#define	GATEWAY_SERVICE_HPP

#include <stdexcept>

#include "gateway_service_api_request.hpp"
#include "gateway_service_api_response.hpp"
#include "service.hpp"

namespace service {
	class GatewayService: public Service<GatewayServiceApiRequest, GatewayServiceApiResponse> {
	public:
		GatewayService() = default;
		GatewayService(const GatewayService&) = delete;
		GatewayService& operator=(const GatewayService&) = delete;
		GatewayServiceApiResponse run_api_request(const GatewayServiceApiRequest& request) override;
	};

	inline GatewayServiceApiResponse GatewayService::run_api_request(const GatewayServiceApiRequest& request) {
		throw std::runtime_error("not implemented");
	}
}

#endif // GATEWAY_SERVICE_HPP