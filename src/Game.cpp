#include "Game.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

Game::Game()
: m_window(sf::VideoMode(1024, 940), "War Plane")
, m_texture()
, m_player()
, m_player_speed(250.f)

// Player Directions
, m_is_moving_up(false)
, m_is_moving_down(false)
, m_is_moving_right(false)
, m_is_moving_left(false) {

    m_texture.loadFromFile("./assets/images/Eagle.png");
    m_player.setTexture(m_texture);

    // Spawn player at the center
    const sf::FloatRect bounds(m_player.getLocalBounds());
    m_player.setOrigin(bounds.width / 2, bounds.height / 2);
    m_player.setPosition(sf::Vector2f(m_window.getSize()) / 2.f);
}

void Game::run() {
    sf::Clock clock;
    sf::Time fps(sf::seconds(1 / 60.f)), time_since_last_update(sf::Time::Zero);

    while(m_window.isOpen()) {
        for(
            time_since_last_update += clock.restart();
            time_since_last_update > fps;
            time_since_last_update -= fps
        ) {
            process_events();
            update(fps);
        }
        
        process_events();
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
    
    if(m_is_moving_up)     velocity.y -= m_player_speed;
    if(m_is_moving_down)   velocity.y += m_player_speed;
    if(m_is_moving_left)   velocity.x -= m_player_speed;
    if(m_is_moving_right)  velocity.x += m_player_speed;

    m_player.move(velocity * dt.asSeconds());
}

void Game::draw() {
    m_window.clear();

    m_window.draw(m_player);

    m_window.display();
}