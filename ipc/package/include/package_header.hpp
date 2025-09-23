#ifndef	PACKAGE_HEADER_HPP
#define	PACKAGE_HEADER_HPP

#include <array>
#include <cstdint>
#include <functional>

namespace ipc {
	template <std::size_t PREAMBLE_SIZE>
	class PackageHeader {
	public:
		using Preamble = std::array<std::uint8_t, PREAMBLE_SIZE>;
		PackageHeader(const Preamble& preamble, const std::size_t payload_size): m_preamble(preamble), m_payload_size(payload_size) {

		}
		PackageHeader(const PackageHeader&) = default;
		PackageHeader& operator=(const PackageHeader&) = default;
		virtual ~PackageHeader() noexcept = default;
		const Preamble& preamble() const {
			return std::ref(m_preamble);
		}
		std::size_t payload_size() const {
			return m_payload_size;
		}
	private:
		Preamble m_preamble;
		std::size_t m_payload_size;
	};
}

#endif // PACKAGE_HEADER_HPP