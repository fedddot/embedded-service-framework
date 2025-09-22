#ifndef	PROCESSOR_HPP
#define	PROCESSOR_HPP

#include <stdexcept>

#include "queue.hpp"

namespace processor {
	template <typename Input, typename Output>
	class Processor {
	public:
		using InputQueue = queue::Queue<Input>;
		using OutputQueue = queue::Queue<Output>;
		
		Processor() = default;
		Processor(const Processor&) = default;
		Processor& operator=(const Processor&) = default;
		
		virtual ~Processor() noexcept = default;
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
	inline void Processor<Input, Output>::set_input_queue(InputQueue *input_queue_ptr) {
		if (!input_queue_ptr) {
			throw std::invalid_argument("received null input_queue_ptr");
		}
		m_input_queue_ptr = input_queue_ptr;
	}

	template <typename Input, typename Output>
	inline void Processor<Input, Output>::set_output_queue(OutputQueue *output_queue_ptr) {
		if (!output_queue_ptr) {
			throw std::invalid_argument("received null output_queue_ptr");
		}
		m_output_queue_ptr = output_queue_ptr;
	}

	template <typename Input, typename Output>
	inline typename Processor<Input, Output>::InputQueue* Processor<Input, Output>::input_queue() const {
		return m_input_queue_ptr;
	}

	template <typename Input, typename Output>
	inline typename Processor<Input, Output>::OutputQueue* Processor<Input, Output>::output_queue() const {
		return m_output_queue_ptr;
	}
}

#endif // PROCESSOR_HPP