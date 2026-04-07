#include "states/Introduction.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include "states/StateStack.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

const sf::Color text_color(0x56, 0xe1, 0xe9);
const sf::Color background_color(0x0a, 0x23, 0x53);

Introduction::Introduction(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_text("Hi there", ctx.fonts->get(Fonts::main)) {
    m_text.setFillColor(text_color);
    center_origin(m_text);
    m_text.setPosition(sf::Vector2f(ctx.window->getSize()) / 2.f);
}

void Introduction::draw() const {
    sf::RenderWindow& window = * get_context().window;

    window.clear(background_color);
    window.draw(m_text);
}

bool Introduction::update(sf::Time& dt) {
    return false;
}

bool Introduction::handle_events(const sf::Event& event) {
    if(event.type == sf::Event::KeyReleased) {
        request_pop();
        request_push(States::Game);
    }

    return false;
}
