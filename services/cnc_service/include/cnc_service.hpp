#ifndef	CNC_SERVICE_HPP
#define	CNC_SERVICE_HPP

#include <stdexcept>

#include "cnc_service_api_request.hpp"
#include "cnc_service_api_response.hpp"
#include "service.hpp"

namespace service {
	class CncService: public Service<CncServiceApiRequest, CncServiceApiResponse> {
	public:
		CncService() = default;
		CncService(const CncService&) = delete;
		CncService& operator=(const CncService&) = delete;
		CncServiceApiResponse run_api_request(const CncServiceApiRequest& request) override {
			throw std::runtime_error("not implemented");
		}
	private:
	};
}

#endif // CNC_SERVICE_HPP