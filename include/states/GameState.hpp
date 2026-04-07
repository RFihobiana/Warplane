#pragma once

#include "World.hpp"
#include "entity/Aircraft.hpp"
#include "entity/Player.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/StateStack.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

class Application {
    public:
        Application();
        void run();

    private:
        void load_resources();
        void initialize_stacks();

        void process_events();
        void update(sf::Time& dt);
        void draw();
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
        Player m_player;

        sf::Text m_text;

        bool m_is_paused;

        StateStack m_stack;
};
