#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game {
    public:
        Game();
        void run();

    private:
        void process_events();
        void update(sf::Time dt);
        void draw();

        // Player movements
        void handle_player_inputs(const sf::Keyboard::Key& key, const bool& is_pressed);
    
    private:
        sf::RenderWindow m_window;

        sf::Texture m_texture;
        sf::Sprite m_player;

        float m_player_speed;
        
        bool m_is_moving_up;
        bool m_is_moving_down;
        bool m_is_moving_right;
        bool m_is_moving_left;
};
