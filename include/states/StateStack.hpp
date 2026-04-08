#pragma once

#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

class StateStack: private sf::NonCopyable {
    public:
        enum Action {
            Push,
            Pop,
            Clear
        };

    public:
        explicit StateStack(State::Context ctx);

        template<typename T>
        void register_state(const States::ID state_id);

        void update(sf::Time& dt);
        void handle_events(const sf::Event& event);
        void draw() const;

        void popState();
        void clearStack();
        void pushState(const States::ID& state_id);

        bool is_empty() const;

    private:
        struct PendingChange {
            Action action;
            States::ID state_id;

            PendingChange(const Action& action, const States::ID& state_id = States::None) 
            : action(action)
            , state_id(state_id) {}
        };

    private:
        void apply_pending_changes();
        State::Ptr create_state(const States::ID& state_id);

    private:
        std::vector<State::Ptr>     m_stack;
        std::vector<PendingChange>  m_pending_list;
        State::Context              m_context;
        std::unordered_map<States::ID, std::function<State::Ptr()>> m_factories;
};

#include "states/StateStack.inl"
