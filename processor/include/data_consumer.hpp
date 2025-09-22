#ifndef	DATA_CONSUMER_HPP
#define	DATA_CONSUMER_HPP

#include "processor.hpp"
#include "queue.hpp"

namespace processor {
	template <typename T>
	class DataConsumer: public Processor {
	public:
		using DataQueue = queue::Queue<T>;
		virtual void set_input_queue(DataQueue *input_queue_ptr) = 0;
	protected:
		virtual DataQueue *input_queue() const = 0;
	};
}

#endif // DATA_CONSUMER_HPP