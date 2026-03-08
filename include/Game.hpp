#pragma once
#include "textures/ResourceIdentifier.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game {
    public:
        Game();
        void run();

    private:
        void load_resources();

        void process_events();
        void update(sf::Time dt);
        void draw();

        // Player movements
        void handle_player_inputs(const sf::Keyboard::Key& key, const bool& is_pressed);

        void update_static_texts(sf::Time dt);
    
    private:
        sf::RenderWindow m_window;

        sf::Sprite m_player, m_background;

        float m_player_speed;
        
        bool m_is_moving_up;
        bool m_is_moving_down;
        bool m_is_moving_right;
        bool m_is_moving_left;

        sf::Text m_text;

        TextureHolder   m_texture_holder;
        FontHolder      m_font_holder;
};
