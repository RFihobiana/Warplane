#include "states/Introduction.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateStack.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

Introduction::Introduction(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_text("Hi there", ctx.fonts->get(Fonts::main)) {
    m_text.setFillColor(sf::Color::Red);
    center_origin(m_text);
    m_text.setPosition(sf::Vector2f(ctx.window->getSize()) / 2.f);
}

void Introduction::draw() const {
    sf::RenderWindow& window = * get_context().window;

    window.clear(sf::Color::Yellow);
    window.draw(m_text);
}

bool Introduction::update(sf::Time& dt) {
    return false;
}

bool Introduction::handle_events(const sf::Event& event) {
    return false;
}
