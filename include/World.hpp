#pragma once

#include "SceneNode.hpp"
#include "command/CommandQueue.hpp"
#include "entity/Aircraft.hpp"
#include "entity/SpriteNode.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>

class World: public sf::NonCopyable {
    public:
        World(sf::RenderWindow& window, TextureHolder& textures);

        void update(sf::Time& dt);
        void draw() const;

        Aircraft& get_player() const;
        const sf::View& get_view() const;

        CommandQueue& get_command_queue();
    
    private:
        
        void load_resources();
        
        /* Build world's entities */
        void build();

    private:
        enum Layer {
            Background,
            Air,
            LayerCount
        };

    private:
        sf::RenderWindow&   m_window;
        TextureHolder&      m_textures;
        
        sf::View        m_view;
        sf::FloatRect   m_world_bound;
        sf::Vector2f    m_scroll_speed;
        
        SceneNode                           m_graph;
        std::array<SceneNode*, LayerCount>  m_layers;

        Aircraft*                           m_player;
        sf::Vector2f        m_spawn_player;

        CommandQueue m_command_queue;

};
