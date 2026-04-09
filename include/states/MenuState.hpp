#pragma once

#include "GUI/Button.hpp"
#include "states/State.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <cstddef>
#include <vector>

class MenuState: public State {
    public:
        MenuState(StateStack& stack, Context& ctx);
        virtual void draw() const;
        virtual bool handle_events(const sf::Event& event);
        virtual bool update(sf::Time& dt);

    private:
        enum Options {
            Play,
            Quit,
            OptionCount,
        };

    private:
        void setup_options();
        void setup_background();

    private:
        std::array<sf::Text, OptionCount> m_options;
        std::size_t m_selected_option;

        std::vector<sf::RectangleShape> m_backgrounds;
        GUI::Button::Ptr btn;
};
