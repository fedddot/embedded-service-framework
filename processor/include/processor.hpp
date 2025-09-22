#ifndef	PROCESSOR_HPP
#define	PROCESSOR_HPP

namespace processor {
	class Processor {
	public:
		virtual ~Processor() noexcept = default;
		virtual void process() = 0;
	};
}

#endif // PROCESSOR_HPP