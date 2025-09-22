#ifndef	DATA_PRODUCER_HPP
#define	DATA_PRODUCER_HPP

#include "queue.hpp"

namespace processor {
	template <typename T>
	class DataProducer {
	public:
		using DataQueue = queue::Queue<T>;
		virtual ~DataProducer() noexcept = default;
		virtual void set_output_queue(DataQueue *output_queue_ptr) = 0;
	protected:
		virtual DataQueue *output_queue() const = 0;
	};
}

#endif // DATA_PRODUCER_HPP