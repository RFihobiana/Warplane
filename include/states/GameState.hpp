#pragma once

#include "World.hpp"
#include "states/State.hpp"
#include "states/StateStack.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameState: public State {
    public:
        GameState(StateStack& stack, Context& ctx);

    private:
        void load_resources();

        virtual bool handle_events(const sf::Event& event);
        virtual bool update(sf::Time& dt);
        virtual void draw() const;
    
    private:
        World           m_world;
};
