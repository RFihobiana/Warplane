#pragma once

#include "SceneNode.hpp"
#include "entity/Aircraft.hpp"
#include "entity/SpriteNode.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>

class World {
    public:
        World(sf::RenderWindow& window, TextureHolder& textures);

        void update(sf::Time& dt);
        void draw() const;

        Aircraft& get_player() const;
        const sf::View& get_view() const;
    
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
        sf::Vector2f        m_spawn_player;
        
        sf::View        m_view;
        sf::Vector2f    m_view_speed;
        
        SceneNode                           m_graph;
        std::array<SceneNode*, LayerCount>  m_layers;
        Aircraft*                           m_player;

};
