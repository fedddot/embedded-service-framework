#ifndef	LINEAR_MOVEMENT_DATA_HPP
#define	LINEAR_MOVEMENT_DATA_HPP

#include <functional>

#include "cnc_data.hpp"

namespace service {
	class LinearMovementData {
	public:
		LinearMovementData(
			const Vector<double>& axes_basis,
			const Vector<double>& target_position,
			const double& linear_speed
		): m_axes_basis(axes_basis), m_target_position(target_position), m_linear_speed(linear_speed) {}
		LinearMovementData(const LinearMovementData&) = default;
		LinearMovementData& operator=(const LinearMovementData&) = default;
		virtual ~LinearMovementData() noexcept = default;
		const Vector<double>& axes_basis() const { return std::ref(m_axes_basis); }
		const Vector<double>& target_position() const { return std::ref(m_target_position); }
		const double& linear_speed() const { return std::ref(m_linear_speed); }
	private:
		Vector<double> m_axes_basis;
		Vector<double> m_target_position;
		double m_linear_speed;
	};
}

#endif // LINEAR_MOVEMENT_DATA_HPP