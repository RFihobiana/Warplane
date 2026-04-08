#include "states/StateStack.hpp"
#include "states/StateIdentification.hpp"
#include <SFML/System/Time.hpp>
#include <cassert>

StateStack::StateStack(State::Context ctx): m_context(ctx) {}

void StateStack::update(sf::Time& dt) {
    for(auto iter = m_stack.rbegin(); iter != m_stack.rend(); iter++) {
        if(!(*iter)->update(dt)) break;
    }

    apply_pending_changes();
}

void StateStack::handle_events(const sf::Event& event) {
    for(auto iter = m_stack.rbegin(); iter != m_stack.rend(); iter++) {
        if(!(*iter)->handle_events(event)) break;
    }

    apply_pending_changes();
}

void StateStack::draw() const {
    for(auto& state: m_stack) {
        state->draw();
    }
}

void StateStack::popState() {
    m_pending_list.push_back(PendingChange(Pop));
}

void StateStack::clearStack() {
    m_pending_list.push_back(PendingChange(Clear));
}

void StateStack::pushState(const States::ID& state_id) {
    m_pending_list.push_back(PendingChange(Push, state_id));
}

void StateStack::apply_pending_changes() {
    for(const auto& changement: m_pending_list) {
        switch (changement.action) {
            case Pop:
                m_stack.pop_back();
                break;

            case Clear:
                m_stack.clear();
                break;

            case Push:
                m_stack.push_back(create_state(changement.state_id));
                break;
        }
    }

    m_pending_list.clear();
}

State::Ptr StateStack::create_state(const States::ID& state_id) {
    auto found = m_factories.find(state_id);
    assert(found != m_factories.end());

    return found->second();
}

bool StateStack::is_empty() const {
    return m_stack.empty();
}
