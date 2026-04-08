#pragma once

#include "states/State.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
class PauseState: public State {
    public:
        PauseState(StateStack& stack, Context& ctx);

        virtual void draw() const;
        virtual bool update(sf::Time& dt);
        virtual bool handle_events(const sf::Event& event);

    private:
        sf::Color m_bg_color;
        sf::RectangleShape m_background;
};
