#pragma once

#include "GUI/Button.hpp"
#include "GUI/Container.hpp"
#include "states/State.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <array>
#include <string>

class SettingState: public State {
    public:
        SettingState(StateStack& stack, Context& ctx);
        virtual void draw() const;
        virtual bool update(sf::Time& dt);
        virtual bool handle_events(const sf::Event& event);

    private:
        void add_button(const Player::Action action, const std::string& text, const float y);

    private:
        std::array<GUI::Button::Ptr, Player::ActionCount> m_button_binding;
        GUI::Container m_GUIContainer;
        sf::RectangleShape m_backgrounds;
};
