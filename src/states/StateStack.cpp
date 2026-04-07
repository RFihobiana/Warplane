#include "states/StateStack.hpp"
#include "states/StateIdentification.hpp"
#include <SFML/System/Time.hpp>

StateStack::StateStack(State::Context ctx): m_context(ctx) {}

void StateStack::update(sf::Time& dt) {
    for(auto& state: m_stack) {
        if(!state->update(dt)) break;
    }

    apply_pending_changes();
}

void StateStack::handle_events(const sf::Event& event) {
    for(auto& state: m_stack) {
        if(!state->handle_events(event)) break;
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
    return m_factories[state_id]();
}

bool StateStack::is_empty() const {
    return m_stack.empty();
}
