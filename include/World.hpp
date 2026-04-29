#pragma once

#include "SceneNode.hpp"
#include "command/CommandQueue.hpp"
#include "entity/Aircraft.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <vector>

class World: public sf::NonCopyable {
    public:
        World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);

        void update(sf::Time& dt);
        void draw() const;

        Aircraft& get_player() const;
        const sf::View& get_view() const;

        CommandQueue& get_command_queue();
    
    private:
        
        void load_resources();
        
        /* Build world's entities */
        void build();

        sf::FloatRect get_battlefield_bounds() const;
        void spawn_enemies();
        void add_enemy(const Aircraft::Type type, float relx, float rely);
        void add_enemies();

    private:
        enum Layer {
            Background,
            Air,
            LayerCount
        };

        struct SpawnPoint {
            SpawnPoint(const Aircraft::Type type, const float x, const float y)
            : type(type)
            , x(x)
            , y(y) {}

            Aircraft::Type type;
            float x;
            float y;
        };

    private:
        sf::RenderWindow&   m_window;
        TextureHolder&      m_textures;
        FontHolder&         m_fonts;
        
        sf::View        m_view;
        sf::FloatRect   m_world_bound;
        sf::Vector2f    m_scroll_speed;
        
        SceneNode                           m_graph;
        std::array<SceneNode*, LayerCount>  m_layers;

        Aircraft*                           m_player;
        sf::Vector2f        m_spawn_player;
        std::vector<SpawnPoint> m_enemy_spawn_points;

        CommandQueue m_command_queue;

};
