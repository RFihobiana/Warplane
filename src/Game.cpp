
#include "Game.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

Game::Game()
: m_window(sf::VideoMode(1024, 940), "War Plane"){}

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
        if(event.type == sf::Event::Closed) m_window.close();
    }
}

void Game::update(sf::Time dt) {}

void Game::draw() {
    m_window.clear();

    m_window.display();
}
