#include "states/PauseState.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include "states/StateStack.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

PauseState::PauseState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_bg_color(0x0, 0x0, 0x0, 0x80)
, m_background(ctx.window->getDefaultView().getSize()) {
    m_background.setFillColor(m_bg_color);
}

void PauseState::draw() const {
    sf::RenderWindow& window = *get_context().window;
    window.setView(window.getDefaultView());

    window.draw(m_background);
}

bool PauseState::update(sf::Time& dt) {
    return false;
}

bool PauseState::handle_events(const sf::Event& event) {
    if(event.type == sf::Event::KeyReleased) {
        // <Delete> Go to Menu
        if(event.key.code == sf::Keyboard::BackSpace) {
            request_pop();
            request_pop();
            request_push(States::MainMenu);
        }

        // <Escape> Return to the game
        if(event.key.code == sf::Keyboard::Escape) {
            request_pop();
        }
    }

    return false;
}
