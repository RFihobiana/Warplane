#include "states/Introduction.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include "states/StateStack.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include <sstream>
#include <string>

const sf::Color text_color(0xbf, 0xaf, 0x42);
const sf::Color background_color(0x10, 0x74, 0xa6);

Introduction::Introduction(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_text("", ctx.fonts->get(Fonts::Hanalei), 64) {
    
    // Load Instruction
    std::ifstream f("./assets/data/intro.txt");
    std::stringstream instruction_simple_text;
    while(!f.eof()) {
        std::string line;
        std::getline(f, line);
        instruction_simple_text << line << '\n';
    }

    f.close();
    
    m_text.setString(instruction_simple_text.str());
    m_text.setStyle(sf::Text::Bold);

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
        request_push(States::MainMenu);
    }

    return false;
}
