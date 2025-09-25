#ifndef	LINEAR_MOVEMENT_MODEL_HPP
#define	LINEAR_MOVEMENT_MODEL_HPP

#include <cmath>
#include <optional>
#include <stdexcept>
#include <utility>

#include "cnc_data.hpp"
#include "linear_movement_data.hpp"

namespace service {
	class LinearMovementModel {
	public:
		struct MovementStep {
			std::vector<std::pair<Axis, MotorDirection>> steps;
			double step_duration;
		};
		LinearMovementModel(const LinearMovementData& data): m_data(data), m_current_position(0.0, 0.0, 0.0) {
			for (const auto& axis: {Axis::X, Axis::Y, Axis::Z}) {
				if (m_data.axes_basis().get(axis) == 0.0) {
					throw std::invalid_argument("axis basis cannot be zero");
				}
			}
		}
		LinearMovementModel(const LinearMovementModel&) = default;
		LinearMovementModel& operator=(const LinearMovementModel&) = default;
		virtual ~LinearMovementModel() noexcept = default;
		std::optional<MovementStep> next_step() {
			return std::nullopt;
		}
	private:
		LinearMovementData m_data;
		Vector<double> m_current_position;
		static double evaluate_vector_length(const Vector<double>& vec) {
			double sum = 0.0;
			for (const auto& axis: {Axis::X, Axis::Y, Axis::Z}) {
				sum += vec.get(axis) * vec.get(axis);
			}
			return std::sqrt(sum);
		}
		static Vector<double> evaluate_velocity_vector(const Vector<double>& target, const double linear_speed, const double total_length) {
			Vector<double> velocity(0.0, 0.0, 0.0);
			if ((total_length <= 0.0) || (linear_speed <= 0.0)) {
				throw std::invalid_argument("both total length and linear speed must have positive non-zero value");
			}
			for (const auto& axis: {Axis::X, Axis::Y, Axis::Z}) {
				velocity.set(axis, linear_speed * target.get(axis) / total_length);
			}
			return velocity;
		}
	};
}

#endif // LINEAR_MOVEMENT_MODEL_HPP