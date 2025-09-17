#ifndef	DATA_WRITER_HPP
#define	DATA_WRITER_HPP

namespace ipc {
	template <typename Data>
	class DataWriter {
	public:
		virtual ~DataWriter() noexcept = default;
		virtual void write(const Data& data) = 0;
	};
}

#endif // DATA_WRITER_HPP