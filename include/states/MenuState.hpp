#pragma once

#include "states/State.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class MenuState: public State {
    public:
        MenuState(StateStack& stack, Context& ctx);
        virtual void draw() const;
        virtual bool handle_events(const sf::Event& event);
        virtual bool update(sf::Time& dt);

    private:
        void setup_options();
        void setup_background();

    private:
        std::vector<sf::RectangleShape> m_backgrounds;
};
