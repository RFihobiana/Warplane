#include "states/PauseState.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include "states/StateStack.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <sstream>
#include <string>

PauseState::PauseState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_bg_color(0x0, 0x0, 0x0, 0x80)
, m_background(ctx.window->getDefaultView().getSize())
, m_pause_title("Game Paused", ctx.fonts->get(Fonts::main), 68)
, m_instruction("", ctx.fonts->get(Fonts::main)) {
    m_background.setFillColor(m_bg_color);

    sf::Vector2f view_size(ctx.window->getDefaultView().getSize());

    center_origin(m_pause_title);
    m_pause_title.setPosition(
        view_size.x * 0.5f,
        view_size.y * 0.30f
    );

    // Instructions
    std::ifstream file("./assets/data/pause_instruction.txt");
    std::stringstream lines;
    while(!file.eof()) {
        std::string line;
        std::getline(file, line);
        lines << line << std::endl;
    }
    
    file.close();

    m_instruction.setString(lines.str());
    center_origin(m_instruction);
    m_instruction.setPosition(
        view_size.x * 0.5f,
        view_size.y * 0.85f
    );
    
}

void PauseState::draw() const {
    sf::RenderWindow& window = *get_context().window;
    window.setView(window.getDefaultView());

    window.draw(m_background);
    window.draw(m_pause_title);
    window.draw(m_instruction);
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
