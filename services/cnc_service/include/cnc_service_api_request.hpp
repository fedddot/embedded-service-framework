#ifndef	CNC_SERVICE_API_REQUEST_HPP
#define	CNC_SERVICE_API_REQUEST_HPP

#include <functional>

namespace service {
	template <typename RouteId, typename Payload>
	class CncServiceApiRequest {
	public:
		CncServiceApiRequest(
			const RouteId& route_id,
			const Payload& payload
		): m_route_id(route_id), m_payload(payload) {}
		CncServiceApiRequest(const CncServiceApiRequest&) = default;
		CncServiceApiRequest& operator=(const CncServiceApiRequest&) = default;
		virtual ~CncServiceApiRequest() noexcept = default;
		const RouteId& route_id() const { return std::ref(m_route_id); }
		const Payload& payload() const { return std::ref(m_payload); }
	private:
		RouteId m_route_id;
		Payload m_payload;
	};
}

#endif // CNC_SERVICE_API_REQUEST_HPP