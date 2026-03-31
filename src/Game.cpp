#include "Game.hpp"
#include "entity/Aircraft.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <string>
#include <utility>

Game::Game()
: m_window(sf::VideoMode(1240, 940), "War Plane")
, m_world(m_window, m_textures)
, m_player(m_world.get_player())

// Static text
, m_text() {
    load_resources();

    // Setup fonts
    m_text.setFont(m_font_holder.get(Fonts::main));
}

void Game::load_resources() {
    // Fonts
    m_font_holder.load(Fonts::main, "./assets/fonts/Sansation.ttf");
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
            update_static_texts(fps);
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
    if(key == sf::Keyboard::W)      m_player.move_up(is_pressed);
    else if(key == sf::Keyboard::S) m_player.move_down(is_pressed);
    else if(key == sf::Keyboard::D) m_player.move_right(is_pressed);
    else if(key == sf::Keyboard::A) m_player.move_left(is_pressed);
}

void Game::update(sf::Time& dt) {
    m_world.update(dt);
}

void Game::update_static_texts(sf::Time dt) {
    static sf::Time elapsed_time(sf::Time::Zero);
    static long long frame_count = 0, last_frame_count = 0;

    elapsed_time += dt;
    
    if(elapsed_time >= sf::seconds(1.f)) {
        // Update fps resulted value for the screen and reset counters 
        last_frame_count = frame_count;
        elapsed_time = sf::Time::Zero;
        frame_count = 0;
    } else {
        frame_count++;
    }

    m_text.setString("FPS: " + std::to_string(last_frame_count));
    const sf::View& world_view(m_world.get_view());
    sf::Vector2f view_position =  sf::Vector2f(world_view.getCenter() - (world_view.getSize() / 2.f));
    m_text.setPosition(view_position);
}

void Game::draw() {
    m_window.clear();

    m_world.draw();
    m_window.draw(m_text);

    m_window.setView(m_window.getDefaultView());
    m_window.display();
}