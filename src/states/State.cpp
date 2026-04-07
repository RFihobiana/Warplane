#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include "states/StateStack.hpp"

State::State(StateStack& stack, Context& ctx)
: m_stack(stack)
, m_context(ctx) {}

State::Context State::get_context() const {
    return m_context;
}

void State::request_pop() {
    m_stack.popState();
}

void State::request_clear() {
    m_stack.clearStack();
}

void State::request_push(const States::ID& state_id) {
    m_stack.pushState(state_id);
}


