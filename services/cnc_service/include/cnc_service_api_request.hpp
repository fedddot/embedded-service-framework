#ifndef	CNC_SERVICE_API_REQUEST_HPP
#define	CNC_SERVICE_API_REQUEST_HPP

#include <functional>
#include <optional>

#include "circular_movement_data.hpp"
#include "linear_movement_data.hpp"

namespace service {
	class CncServiceApiRequest {
	public:
		enum class MovementType: int {
			LINEAR = 0,
			CIRCULAR = 1
		};
		CncServiceApiRequest(
			const MovementType& movement_type,
			const std::optional<CircularMovementData>& circular_movement_data,
			const std::optional<LinearMovementData>& linear_movement_data
		): m_movement_type(movement_type), m_circular_movement_data(circular_movement_data), m_linear_movement_data(linear_movement_data) {}
		CncServiceApiRequest(const CncServiceApiRequest&) = default;
		CncServiceApiRequest& operator=(const CncServiceApiRequest&) = default;
		virtual ~CncServiceApiRequest() noexcept = default;
		const MovementType& movement_type() const { return std::ref(m_movement_type); }
		const std::optional<CircularMovementData>& circular_movement_data() const { return std::ref(m_circular_movement_data); }
		const std::optional<LinearMovementData>& linear_movement_data() const { return std::ref(m_linear_movement_data); }
	private:
		MovementType m_movement_type;
		std::optional<CircularMovementData> m_circular_movement_data;
		std::optional<LinearMovementData> m_linear_movement_data;
	};
}

#endif // CNC_SERVICE_API_REQUEST_HPP