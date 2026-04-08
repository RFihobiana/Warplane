#pragma once

#include "states/ParallelTask.hpp"
#include "states/State.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
class LoadingState: public State {
    public:
        LoadingState(StateStack& stack, Context& ctx);

        virtual void draw() const;
        virtual bool handle_events(const sf::Event& event);
        virtual bool update(sf::Time& dt);

    private:
        // Change progress bar's length
        // `percent`: [0; 1]
        void set_completion(float percent);

    private:
        sf::Text    m_loading_text;
        sf::RectangleShape  m_progress_bar_bg;
        sf::RectangleShape  m_progress_bar;
        ParallelTask    m_task;
};
