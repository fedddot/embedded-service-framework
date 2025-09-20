#ifndef	INPUT_STREAM_HPP
#define	INPUT_STREAM_HPP

#include <cstddef>

namespace ipc {
	template <typename T>
	class InputStream {
	public:
		virtual ~InputStream() noexcept = default;
		virtual T read() = 0;
		virtual const T& inspect(const std::size_t index) const = 0;
		virtual std::size_t size() const = 0;
		virtual void clear() = 0;
	};
}

#endif // INPUT_STREAM_HPP