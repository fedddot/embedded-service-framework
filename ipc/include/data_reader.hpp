#ifndef	DATA_READER_HPP
#define	DATA_READER_HPP

namespace ipc {
	template <typename Data>
	class DataReader {
	public:
		virtual ~DataReader() noexcept = default;
		virtual Data read() = 0;
	};
}

#endif // DATA_READER_HPP