#ifndef	RELATIONSHIP_HPP
#define	RELATIONSHIP_HPP

#include <stdexcept>

#include "queue.hpp"

namespace processor {
	template <typename Input, typename Output>
	class Relationship {
	public:
		using InputQueue = queue::Queue<Input>;
		using OutputQueue = queue::Queue<Output>;
		
		Relationship() = default;
		Relationship(const Relationship&) = default;
		Relationship& operator=(const Relationship&) = default;
		
		virtual ~Relationship() noexcept = default;
		virtual void process() = 0;
		
		void set_input_queue(InputQueue *input_queue_ptr);
		void set_output_queue(OutputQueue *output_queue_ptr);
	protected:
		InputQueue *input_queue() const;
		OutputQueue *output_queue() const;
	private:
		InputQueue *m_input_queue_ptr;
		OutputQueue *m_output_queue_ptr;
	};

	template <typename Input, typename Output>
	inline void Relationship<Input, Output>::set_input_queue(InputQueue *input_queue_ptr) {
		if (!input_queue_ptr) {
			throw std::invalid_argument("received null input_queue_ptr");
		}
		m_input_queue_ptr = input_queue_ptr;
	}

	template <typename Input, typename Output>
	inline void Relationship<Input, Output>::set_output_queue(OutputQueue *output_queue_ptr) {
		if (!output_queue_ptr) {
			throw std::invalid_argument("received null output_queue_ptr");
		}
		m_output_queue_ptr = output_queue_ptr;
	}

	template <typename Input, typename Output>
	inline typename Relationship<Input, Output>::InputQueue* Relationship<Input, Output>::input_queue() const {
		if (!m_input_queue_ptr) {
			throw std::runtime_error("input_queue_ptr not set");
		}
		return m_input_queue_ptr;
	}

	template <typename Input, typename Output>
	inline typename Relationship<Input, Output>::OutputQueue* Relationship<Input, Output>::output_queue() const {
		if (!m_output_queue_ptr) {
			throw std::runtime_error("output_queue_ptr not set");
		}
		return m_output_queue_ptr;
	}
}

#endif // RELATIONSHIP_HPP