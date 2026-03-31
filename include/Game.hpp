#pragma once
#include "SceneNode.hpp"
#include "World.hpp"
#include "entity/Aircraft.hpp"
#include "resources/ResourceIdentifier.hpp"
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
        void update(sf::Time& dt);
        void draw();

        // Player movements
        void handle_player_inputs(const sf::Keyboard::Key& key, const bool& is_pressed);

        void update_static_texts(sf::Time dt);
    
    private:
        enum Layers {
            Background,
            Air,
            LayourCount,
        };
    
    private:
        sf::RenderWindow m_window;
        
        TextureHolder   m_textures;
        FontHolder      m_font_holder;

        World m_world;
        Aircraft& m_player;

        sf::Text m_text;
};
