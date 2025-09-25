#ifndef	CIRCULAR_MOVEMENT_DATA_HPP
#define	CIRCULAR_MOVEMENT_DATA_HPP

#include <functional>

#include "cnc_data.hpp"

namespace service {
	class CircularMovementData {
	public:
		CircularMovementData(
			const Vector<double>& origin_position,
			const Vector<double>& rotation_center,
			const Axis& rotation_axis,
			const double rotation_angle,
			const double rotation_speed
		): m_origin_position(origin_position), m_rotation_center(rotation_center), m_rotation_axis(rotation_axis), m_rotation_angle(rotation_angle), m_rotation_speed(rotation_speed) {}
		CircularMovementData(const CircularMovementData&) = default;
		CircularMovementData& operator=(const CircularMovementData&) = default;
		virtual ~CircularMovementData() noexcept = default;
		const Vector<double>& origin_position() const { return std::ref(m_origin_position); }
		const Vector<double>& rotation_center() const { return std::ref(m_rotation_center); }
		const Axis& rotation_axis() const { return std::ref(m_rotation_axis); }
		const double& rotation_angle() const { return std::ref(m_rotation_angle); }
		const double& rotation_speed() const { return std::ref(m_rotation_speed); }
	private:
		Vector<double> m_origin_position;
		Vector<double> m_rotation_center;
		Axis m_rotation_axis;
		double m_rotation_angle;
		double m_rotation_speed;
	};
}

#endif // CIRCULAR_MOVEMENT_DATA_HPP