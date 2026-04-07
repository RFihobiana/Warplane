#pragma once

#include "states/State.hpp"
#include <SFML/Graphics/Text.hpp>

class Introduction: public State {
    public:
        Introduction(StateStack& stack, Context& ctx);
        
        virtual void draw() const;
        virtual bool update(sf::Time& dt);
        virtual bool handle_events(const sf::Event& event);

    private:
        sf::Text m_text;
};
