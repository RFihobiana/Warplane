#include "states/MenuState.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <array>
#include <cstddef>

MenuState::MenuState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_selected_option(0) {
    setup_options();
    setup_background();
}

void MenuState::setup_options() {
    sf::Text play("Play", get_context().fonts->get(Fonts::main));
    sf::Text quit("Quit", get_context().fonts->get(Fonts::main));
    
    m_options[Play] = play;
    m_options[Quit] = quit;

    const float distance_between = 50.f;
    const sf::Vector2f from_pos = sf::Vector2f(get_context().window->getSize()) / 2.5f;
    for(size_t i = 0; i < m_options.size(); i++) {
        sf::Text& text(m_options[i]);
        
        sf::Vector2f position(
            0.f,
            distance_between * i
        );

        text.setPosition(from_pos + position);
    }
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

    for(const auto& shape: m_backgrounds) {
        window.draw(shape);
    }

    for(const sf::Text& text: m_options) {
        window.draw(text);
    }
}

bool MenuState::handle_events(const sf::Event& event) {
    if(event.type == sf::Event::KeyReleased) {
        if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
            m_selected_option = (m_selected_option - 1) % m_options.size();
        }

        else if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            m_selected_option = (m_selected_option + 1) % m_options.size();
        }
    }
    return false;
}

bool MenuState::update(sf::Time& dt) {
    const sf::Color default_color(sf::Color::White);
    const sf::Color selected_color(sf::Color::Red);

    for(sf::Text& text: m_options) {
        text.setFillColor(default_color);
    }

    m_options[m_selected_option].setFillColor(selected_color);

    return false;
}

