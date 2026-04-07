#include "states/State.hpp"

State::State(StateStack& stack, Context& ctx)
: m_stack(stack)
, m_context(ctx) {}

State::Context State::get_context() const {
    return m_context;
}




