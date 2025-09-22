#ifndef	QUEUE_HPP
#define	QUEUE_HPP

#include <cstddef>

namespace queue {
	template <typename T>
	class Queue {
	public:
		virtual ~Queue() noexcept = default;
		virtual void enqueue(const T& item) = 0;
		virtual T dequeue() = 0;
		virtual void copy_elements(T *dst, const std::size_t len) const = 0;
		virtual std::size_t size() const = 0;
		virtual void clear() = 0;
	};
}

#endif // QUEUE_HPP