
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
, m_player(32)

// Player Directions
, m_is_moving_up(false)
, m_is_moving_down(false)
, m_is_moving_right(false)
, m_is_moving_left(false) {

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

        else if(event.type == sf::Event::KeyPressed) handle_player_inputs(event.key.code, true);

        else if(event.type == sf::Event::KeyReleased) handle_player_inputs(event.key.code, false);
    }
}

void Game::handle_player_inputs(const sf::Keyboard::Key& key, const bool& is_pressed) {
    if(key == sf::Keyboard::W)      m_is_moving_up      = is_pressed;
    else if(key == sf::Keyboard::S) m_is_moving_down    = is_pressed;
    else if(key == sf::Keyboard::A) m_is_moving_left    = is_pressed;
    else if(key == sf::Keyboard::D) m_is_moving_right   = is_pressed;
}

void Game::update(sf::Time dt) {
    sf::Vector2f velocity;
    
    if(m_is_moving_up)     velocity.y -= 1.f;
    if(m_is_moving_down)   velocity.y += 1.f;
    if(m_is_moving_left)   velocity.x -= 1.f;
    if(m_is_moving_right)  velocity.x += 1.f;

    m_player.move(velocity * dt.asSeconds());
}

void Game::draw() {
    m_window.clear();

    m_window.draw(m_player);

    m_window.display();
}