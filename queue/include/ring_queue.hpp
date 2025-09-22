#ifndef	RING_QUEUE_HPP
#define	RING_QUEUE_HPP

#include <cstddef>
#include <stdexcept>

#include "queue.hpp"

namespace queue {
	template <typename T, std::size_t N>
	class RingQueue: public Queue<T> {
	public:
		RingQueue(): m_data{}, m_read_index(0), m_write_index(0), m_size(0) {

		}
		RingQueue(const RingQueue&) = delete;
		RingQueue& operator=(const RingQueue&) = delete;

		void enqueue(const T& elem) override {
			if (m_size == N) {
				throw std::overflow_error("buffer overflow");
			}
			m_data[m_write_index] = elem;
			m_write_index = next_index(m_write_index);
			++m_size;
		}
		T dequeue() override {
			if (m_size == 0) {
				throw std::runtime_error("buffer is empty");
			}
			const auto elem = m_data[m_read_index];
			m_read_index = next_index(m_read_index);
			--m_size;
			return elem;
		}

		void copy_elements(T *dst, const std::size_t len) const override {
			if (!dst) {
				throw std::invalid_argument("dst is nullptr");
			}
			if (len > m_size) {
				throw std::out_of_range("len is out of range");
			}
			auto index = m_read_index;
			for (std::size_t i = 0; i < len; ++i) {
				dst[i] = m_data[index];
				index = next_index(index);
			}
		}
		std::size_t size() const override {
			return m_size;
		}
		std::size_t capacity() const {
			return N;
		}
		void clear() override {
			m_read_index = 0;
			m_write_index = 0;
			m_size = 0;
		}
	private:
		std::array<T, N> m_data;
		std::size_t m_read_index;
		std::size_t m_write_index;
		std::size_t m_size;

		static std::size_t next_index(const std::size_t& index) {
			return (index + 1) % N;
		}
	};
}

#endif // RING_QUEUE_HPP