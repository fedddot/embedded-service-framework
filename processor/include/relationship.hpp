#ifndef	RELATIONSHIP_HPP
#define	RELATIONSHIP_HPP

#include <functional>
#include <memory>
#include <stdexcept>

#include "data_consumer.hpp"
#include "data_producer.hpp"
#include "queue.hpp"

namespace processor {
	template <typename T>
	class Relationship {
	public:
		using DataQueueCtor = std::function<queue::Queue<T> *(void)>;
		Relationship(
			DataProducer<T> *data_producer_ptr,
			DataConsumer<T> *data_consumer_ptr,
			const DataQueueCtor& data_queue_ctor
		): m_data_producer_ptr(data_producer_ptr), m_data_consumer_ptr(data_consumer_ptr), m_data_queue(nullptr) {
			if (!m_data_producer_ptr || !m_data_consumer_ptr || !data_queue_ctor) {
				throw std::invalid_argument("invalid args received");
			}
			m_data_queue.reset(data_queue_ctor());
			if (!m_data_queue) {
				throw std::runtime_error("data_queue_ctor failed to create a queue");
			}
			m_data_producer_ptr->set_output_queue(m_data_queue.get());
			m_data_consumer_ptr->set_input_queue(m_data_queue.get());
		}
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
		DataProducer<T> *m_data_producer_ptr;
		DataConsumer<T> *m_data_consumer_ptr;
		std::unique_ptr<queue::Queue<T>> m_data_queue;
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