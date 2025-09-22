#ifndef	DATA_TRANSFORMER_HPP
#define	DATA_TRANSFORMER_HPP

#include <stdexcept>

#include "data_consumer.hpp"
#include "data_producer.hpp"
#include "processor.hpp"
#include "queue.hpp"

namespace processor {
	template <typename Input, typename Output>
	class DataTransformer: public Processor, public DataConsumer<Input>, public DataProducer<Output> {
	public:
		using InputQueue = queue::Queue<Input>;
		using OutputQueue = queue::Queue<Output>;
		
		DataTransformer() = default;
		DataTransformer(const DataTransformer&) = default;
		DataTransformer& operator=(const DataTransformer&) = default;
		
		virtual void set_input_queue(InputQueue *input_queue_ptr) override;
		virtual void set_output_queue(OutputQueue *output_queue_ptr) override;
	protected:
		virtual InputQueue *input_queue() const override;
		virtual OutputQueue *output_queue() const override;
	private:
		InputQueue *m_input_queue_ptr;
		OutputQueue *m_output_queue_ptr;
	};

	template <typename Input, typename Output>
	inline void DataTransformer<Input, Output>::set_input_queue(InputQueue *input_queue_ptr) {
		if (!input_queue_ptr) {
			throw std::invalid_argument("received null input_queue_ptr");
		}
		m_input_queue_ptr = input_queue_ptr;
	}

	template <typename Input, typename Output>
	inline void DataTransformer<Input, Output>::set_output_queue(OutputQueue *output_queue_ptr) {
		if (!output_queue_ptr) {
			throw std::invalid_argument("received null output_queue_ptr");
		}
		m_output_queue_ptr = output_queue_ptr;
	}

	template <typename Input, typename Output>
	inline typename DataTransformer<Input, Output>::InputQueue* DataTransformer<Input, Output>::input_queue() const {
		if (!m_input_queue_ptr) {
			throw std::runtime_error("input_queue_ptr not set");
		}
		return m_input_queue_ptr;
	}

	template <typename Input, typename Output>
	inline typename DataTransformer<Input, Output>::OutputQueue* DataTransformer<Input, Output>::output_queue() const {
		if (!m_output_queue_ptr) {
			throw std::runtime_error("output_queue_ptr not set");
		}
		return m_output_queue_ptr;
	}
}

#endif // DATA_TRANSFORMER_HPP