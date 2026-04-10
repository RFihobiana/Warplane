#include "states/MenuState.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cstddef>

MenuState::MenuState(StateStack& stack, Context& ctx)
: State(stack, ctx) {
    setup_options();
    setup_background();
}

void MenuState::setup_options() {
}

void MenuState::setup_background() {
    sf::Vector2f window_size(get_context().window->getSize());   

    const size_t counts = 2;
    sf::RectangleShape shape(sf::Vector2f(
        window_size.x / counts,
        window_size.y
    ));

    std::array<unsigned int, 3> rgb {
        0x10,
        0x10,
        0x10
    };
    const std::array<float, 3> step {
        0,
        100,
        150
    };

    for(size_t i = 0; i < counts; i++) {
        sf::Vector2f position(
            shape.getSize().x * i,
            0.f
        );

        shape.setPosition(position);
        m_backgrounds.push_back(shape);
    }

    for(sf::RectangleShape& shape: m_backgrounds) {
        sf::Color color(rgb[0], rgb[1], rgb[2]);
        shape.setFillColor(color);

        rgb[0] = static_cast<unsigned int>(rgb[0] + step[0]) % 255;
        rgb[1] = static_cast<unsigned int>(rgb[1] + step[1]) % 255;
        rgb[2] = static_cast<unsigned int>(rgb[2] + step[2]) % 255;
    }
}

void MenuState::draw() const {
    sf::RenderWindow& window = *get_context().window;
    window.setView(window.getDefaultView());

    for(const auto& shape: m_backgrounds) {
        window.draw(shape);
    }

    GUI::Button btn(*get_context().textures, *get_context().fonts, "Play");
    btn.setPosition(window.getDefaultView().getSize() / 2.f);
    window.draw(btn);
}

bool MenuState::handle_events(const sf::Event& event) {
    return false;
}

bool MenuState::update(sf::Time& dt) {
    return false;
}

