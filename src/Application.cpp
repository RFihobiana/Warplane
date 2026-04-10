#include "Application.hpp"
#include "GUI/Logger.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/GameState.hpp"
#include "states/Introduction.hpp"
#include "states/LoadingState.hpp"
#include "states/MenuState.hpp"
#include "states/PauseState.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
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
#include <memory>
#include <string>

Application::Application()
: m_window(sf::VideoMode(1240, 1024), "War Plane")
, m_player()
, m_text()
, m_logger(std::make_shared<GUI::Logger>(m_textures, m_font_holder))
, m_stack(State::Context(m_window, m_textures, m_font_holder, m_player, *m_logger)) {
    load_resources();
    setup_logger();
    initialize_stacks();

    // Setup fonts
    m_text.setFont(m_font_holder.get(Fonts::main));
    m_stack.pushState(States::Introduction);

    m_logger->add("Ready Launch!");
}

void Application::setup_logger() {
    const sf::Vector2f win_size(m_window.getSize());
    const float bg_percent = 0.30f;
    m_logger->setPosition(
        win_size.x * (1 - bg_percent),
        0.f
    );
    m_logger->set_bg_size(
        win_size.x * bg_percent,
        win_size.y
    );
}

void Application::load_resources() {
    // Fonts
    m_font_holder.load(Fonts::main, "./assets/fonts/Sansation.ttf");
    m_font_holder.load(Fonts::Hanalei, "./assets/fonts/Hanalei.ttf");

    // Textures
    m_textures.load(Textures::ButtonNormal, "./assets/images/buttons/ButtonNormal.png");
    m_textures.load(Textures::ButtonPressed, "./assets/images/buttons/ButtonPressed.png");
    m_textures.load(Textures::ButtonSelected, "./assets/images/buttons/ButtonSelected.png");

    m_logger->add("Resource loaded successfully");
}

void Application::initialize_stacks() {
    m_stack.register_state<Introduction>(States::Introduction);
    m_stack.register_state<GameState>(States::Game);
    m_stack.register_state<MenuState>(States::MainMenu);
    m_stack.register_state<PauseState>(States::Pause);
    m_stack.register_state<LoadingState>(States::Loading);
}

void Application::run() {
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

            if(m_stack.is_empty()) m_window.close();
        }
        
        process_events();
        draw();
    }
}

void Application::process_events() {
    sf::Event event;
    
    while(m_window.pollEvent(event)) {

        if( event.type == sf::Event::Closed) m_window.close();
        
        m_stack.handle_events(event);
    }
}

void Application::update(sf::Time& dt) {
    m_stack.update(dt);
}

void Application::update_static_texts(sf::Time dt) {
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
    sf::Vector2f view_position(0.f, 0.f);
    m_text.setPosition(view_position);
}

void Application::draw() {
    m_window.clear();

    m_stack.draw();
    
    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_text);
    m_window.draw(*m_logger);

    m_window.display();
}