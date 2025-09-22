#include <string>

#include "gtest/gtest.h"

#include "processor.hpp"
#include "ring_queue.hpp"

using namespace processor;
using namespace queue;

using Input = std::string;
using Output = int;

class TestProcessor: public Processor<Input, Output> {
public:
    TestProcessor(): Processor<Input, Output>() {}
    void process() override {
        if (0 == this->input_queue()->size()) {
            return;
        }
        const auto input_message = this->input_queue()->dequeue();
        const auto output_message = static_cast<Output>(std::stoi(input_message));
        this->output_queue()->enqueue(output_message);
    }
};

TEST(ut_processor, process_sanity) {
	// GIVEN
    const auto input_queue_size = 10UL;
    const auto output_queue_size = 10UL;
    const auto input_message = "42";
    const auto expected_output_message = 42;
    
    // WHEN:
	TestProcessor instance;
	
    RingQueue<Input, input_queue_size> input_queue;
	RingQueue<Output, output_queue_size> output_queue;
    ASSERT_NO_THROW(instance.set_input_queue(&input_queue));
    ASSERT_NO_THROW(instance.set_output_queue(&output_queue));
    
	// THEN
    // empty input queue, nothing to do
    ASSERT_NO_THROW(instance.process());
    ASSERT_EQ(output_queue.size(), 0UL);
	
    // non-empty input queue, process one message
    ASSERT_NO_THROW(input_queue.enqueue(input_message));
    ASSERT_NO_THROW(instance.process());
    ASSERT_EQ(input_queue.size(), 0UL);
    ASSERT_EQ(output_queue.size(), 1UL);
    const auto output_message = output_queue.dequeue();
    ASSERT_EQ(output_message, expected_output_message);
}