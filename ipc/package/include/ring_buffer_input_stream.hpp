#ifndef	RING_BUFFER_INPUT_STREAM_HPP
#define	RING_BUFFER_INPUT_STREAM_HPP

#include <array>
#include <cstddef>
#include <stdexcept>

#include "input_stream.hpp"

namespace ipc {
	template <typename T, std::size_t N>
	class RingBufferInputStream: public InputStream<T> {
	public:
		RingBufferInputStream(): m_data{}, m_read_index(0), m_write_index(0), m_size(0) {

		}
		RingBufferInputStream(const RingBufferInputStream&) = delete;
		RingBufferInputStream& operator=(const RingBufferInputStream&) = delete;

		void enqueue(const T& elem) {
			if (m_size == N) {
				throw std::overflow_error("buffer overflow");
			}
			m_data[m_write_index] = elem;
			m_write_index = next_index(m_write_index);
			++m_size;
		}
		T read() override {
			if (m_size == 0) {
				throw std::runtime_error("buffer is empty");
			}
			const auto elem = m_data[m_read_index];
			m_read_index = next_index(m_read_index);
			--m_size;
			return elem;
		}
		const T& inspect(const std::size_t index) const override {
			if (index >= m_size) {
				throw std::out_of_range("index out of range");
			}
			return m_data[(m_read_index + index) % N];
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

#endif // RING_BUFFER_INPUT_STREAM_HPP