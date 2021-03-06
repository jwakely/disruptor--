// Copyright (c) 2011, François Saint-Jacques
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the disruptor-- nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL FRANÇOIS SAINT-JACQUES BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <string>

#include "disruptor/interface.h"

#include "long_event.h"

#ifndef DISRUPTOR_TEST_STUB_EVENT_H_ // NOLINT
#define DISRUPTOR_TEST_STUB_EVENT_H_ // NOLINT


namespace disruptor {
namespace test {

class StubEvent : public LongEvent {
 public:
    StubEvent(const int64_t& value = 0) : LongEvent(value) {}

    std::string test_string() const { return test_string_; }

    void set_test_string(const std::string& test_string) {
        test_string_ = test_string;
    }

 private:
    std::string test_string_;
};

class StubEventFactory : public EventFactoryInterface<StubEvent> {
 public:
    virtual StubEvent* NewInstance(const int& size) const {
        return new StubEvent[size];
    }
};

class StubBatchHandler : public EventHandlerInterface<StubEvent> {
 public:
    virtual void OnEvent(const int64_t& sequence,
                         const bool& end_of_batch,
                         StubEvent* event) {
        if (event)
            event->set_value(sequence);
    };

    virtual void OnStart() {}
    virtual void OnShutdown() {}
};

class StubEventTranslator : public EventTranslatorInterface<StubEvent> {
 public:
    virtual StubEvent* TranslateTo(const int64_t& sequence, StubEvent* event) {
        event->set_value(sequence);
        return event;
    };

};

} // namespace test
} // namespace disruptor

#endif // DISRUPTOR_TEST_LONG_EVENT_H_ NOLINT
