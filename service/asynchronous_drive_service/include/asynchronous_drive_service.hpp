#ifndef	ASYNCHRONOUS_DRIVE_SERVICE_HPP
#define	ASYNCHRONOUS_DRIVE_SERVICE_HPP

#include <stdexcept>

#include "asynchronous_drive_request.hpp"
#include "service.hpp"

namespace service {
	class AsynchronousDriveResponse;

	class AsynchronousDriveService: public Service<AsynchronousDriveRequest, AsynchronousDriveResponse> {
	public:
		AsynchronousDriveResponse run_api_request(const AsynchronousDriveRequest& request) override {
			throw std::runtime_error("not implemented");
		}
	};
}

#endif // ASYNCHRONOUS_DRIVE_SERVICE_HPP