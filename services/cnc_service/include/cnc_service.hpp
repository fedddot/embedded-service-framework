#ifndef	CNC_SERVICE_HPP
#define	CNC_SERVICE_HPP

#include <stdexcept>

#include "circular_movement_data.hpp"
#include "cnc_service_api_request.hpp"
#include "cnc_service_api_response.hpp"
#include "linear_movement_data.hpp"
#include "linear_movement_model.hpp"
#include "service.hpp"

namespace service {
	class CncService: public Service<CncServiceApiRequest, CncServiceApiResponse> {
	public:
		CncService() = default;
		CncService(const CncService&) = delete;
		CncService& operator=(const CncService&) = delete;
		CncServiceApiResponse run_api_request(const CncServiceApiRequest& request) override {
			switch (request.movement_type()) {
			case CncServiceApiRequest::MovementType::LINEAR:
				if (!request.linear_movement_data().has_value()) {
					return CncServiceApiResponse(CncServiceApiResponse::Result::BAD_REQUEST, "missing linear movement data");
				}
				return run_linear_movement_request(request.linear_movement_data().value());
			case CncServiceApiRequest::MovementType::CIRCULAR:
				if (!request.circular_movement_data().has_value()) {
					return CncServiceApiResponse(CncServiceApiResponse::Result::BAD_REQUEST, "missing circular movement data");
				}
				return run_circular_movement_request(request.circular_movement_data().value());
			default:
				return CncServiceApiResponse(CncServiceApiResponse::Result::BAD_REQUEST, "unsupported movement type");
			}
		}
	private:
		CncServiceApiResponse run_linear_movement_request(const LinearMovementData& data) {
			LinearMovementModel model(data);
			throw std::runtime_error("run_linear_movement_request is not implemented yet");
		}
		CncServiceApiResponse run_circular_movement_request(const CircularMovementData& data) {
			throw std::runtime_error("run_circular_movement_request is not implemented yet");
		}
	};
}

#endif // CNC_SERVICE_HPP