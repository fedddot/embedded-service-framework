#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "nanopb_message_writer.hpp"
#include "data_writer.hpp"
#include "pb.h"
#include "pb_encode.h"
#include "test.pb.h"

using namespace ipc;

using ApiMessage = std::string;

class MockPackageWriter : public DataWriter<std::vector<std::uint8_t>> {
public:
    MOCK_METHOD(void, write, (const std::vector<std::uint8_t>&), (override));
};

static bool encode_string(pb_ostream_t *stream, const pb_field_t *field, void *const *arg);

TEST(ut_nanopb_message_writer, write_sanity) {
	// GIVEN
	const auto test_api_message = ApiMessage("test_msg");
	auto package_writer = ::testing::NiceMock<MockPackageWriter>();
	const auto serializer = [](const ApiMessage& data) -> test_api_TestRequest {
		test_api_TestRequest pb_request(test_api_TestRequest_init_default);
		pb_request.request.arg = new std::string(data);
		pb_request.request.funcs.encode = encode_string;
		return pb_request;
	};
	const auto deinit_pb_msg = [](test_api_TestRequest *pb_request) {
		delete (std::string *)((pb_request->request).arg);
	};

	// WHEN
	NanopbMessageWriter<ApiMessage, test_api_TestRequest, 256UL> instance(
		&package_writer,
		serializer,
		deinit_pb_msg,
		test_api_TestRequest_fields
	);

	// THEN
	ASSERT_NO_THROW(instance.write(test_api_message));
}

inline bool encode_string(pb_ostream_t *stream, const pb_field_t *field, void *const *arg) {
	if (!arg) {
		throw std::runtime_error("encode_string called with null arg");
	}
	const auto str = static_cast<const std::string *>(*arg);
	if (!pb_encode_tag_for_field(stream, field)) {
		return false;
	}
	return pb_encode_string(stream, (const pb_byte_t *)(str->c_str()), str->size());
}