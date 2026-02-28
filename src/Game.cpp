
#include "Game.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

Game::Game()
: m_window(sf::VideoMode(1024, 940), "War Plane")
, m_player(32) {

    // Spawn player at the center
    const sf::FloatRect bounds(m_player.getLocalBounds());
    m_player.setOrigin(bounds.width / 2, bounds.height / 2);
    m_player.setPosition(sf::Vector2f(m_window.getSize()) / 2.f);

    // Player color
    m_player.setFillColor(sf::Color::Green);
}

void Game::run() {
    sf::Time fps(sf::seconds(1 / 24.f));
    while(m_window.isOpen()) {
        process_events();
        update(fps);
        draw();
    }
}

void Game::process_events() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if(
            event.type == sf::Event::Closed 
            || (
                event.type == sf::Event::KeyReleased
                && event.key.code == sf::Keyboard::Escape
            )
        ) m_window.close();
    }
}

void Game::update(sf::Time dt) {}

void Game::draw() {
    m_window.clear();

    m_window.draw(m_player);

    m_window.display();
}
