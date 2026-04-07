#include "states/Introduction.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateStack.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Introduction::Introduction(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_text("Hi there", ctx.fonts->get(Fonts::main)) {
    m_text.setFillColor(sf::Color::Red);
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
