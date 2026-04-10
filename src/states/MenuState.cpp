#include "states/MenuState.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
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
#include <memory>

MenuState::MenuState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_container() {
    m_container.setPosition(ctx.window->getDefaultView().getSize() * 0.2f);
    setup_options();
    setup_background();
}

void MenuState::setup_options() {
    const FontHolder& fonts = *get_context().fonts;
    const TextureHolder& textures = *get_context().textures;
    const float SPACE_BETWEEN = 60.f;

    GUI::Label::Ptr title = std::make_shared<GUI::Label>(fonts, "Let's Fly!");
    m_container.pack(title);

    GUI::Button::Ptr start = std::make_shared<GUI::Button>(textures, fonts, "Start");
    start->setPosition(title->getPosition() + sf::Vector2f(0.f, SPACE_BETWEEN));
    start->set_toggle(true);
    
    start->set_callback([this] (){
        request_pop();
        request_push(States::Loading);
    });

    m_container.pack(start);
    
    GUI::Button::Ptr quit = std::make_shared<GUI::Button>(textures, fonts, "Quit");
    quit->setPosition(start->getPosition() + sf::Vector2f(0.f, SPACE_BETWEEN));
    quit->set_toggle(true);

    quit->set_callback([this]() {
        request_pop();
    });
    m_container.pack(quit);
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
    
    window.draw(m_container);
}

bool MenuState::handle_events(const sf::Event& event) {
    m_container.handle_events(event);
    return false;
}

bool MenuState::update(sf::Time& dt) {
    return false;
}

