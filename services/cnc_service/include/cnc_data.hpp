#ifndef	CNC_DATA_HPP
#define	CNC_DATA_HPP

#include <map>

namespace service {
	enum class Axis: int {
		X = 0,
		Y = 1,
		Z = 2
	};

	enum class MotorDirection: int {
		CW = 0,
		CCW = 1,
	};
	
	template <typename T>
	class Vector {
	public:
		Vector(const T& x, const T& y, const T& z): m_data {{Axis::X, x}, {Axis::Y, y}, {Axis::Z, z}} {}
		Vector(const Vector&) = default;
		Vector& operator=(const Vector&) = default;
		virtual ~Vector() noexcept = default;
		const T& get(const Axis& axis) const { return m_data.at(axis); }
		void set(const Axis& axis, const T& value) { m_data[axis] = value; }
	private:
		std::map<Axis, T> m_data;
	};
}

#endif // CNC_DATA_HPP