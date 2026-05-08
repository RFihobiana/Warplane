#pragma once

#include "Entity.hpp"
#include "SceneNode.hpp"
#include "TextNode.hpp"
#include "command/Command.hpp"
#include "command/CommandQueue.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <cstddef>
class Aircraft: public Entity {
    public:
        enum Type {
            Eagle,
            Raptor,
            Avenger,
            TypeCount,
        };
    
    public:
        explicit Aircraft(const Type type, const TextureHolder& textures, const FontHolder& fonts);

        void fire();
        void launch_missile();

        virtual unsigned int get_category() const;
    
    private:
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
        
        virtual void update_current(sf::Time& dt, CommandQueue& commands);
        void update_movement_pattern(sf::Time& dt);

        void check_projectile_launch(sf::Time& dt, CommandQueue& commands);

        void create_bullets(SceneNode& layer, const TextureHolder& textures);
        void create_missile(SceneNode& layer, const TextureHolder& textures);
    
    private:
        Type m_type;
        sf::Sprite m_sprite;
        TextNode* m_health_display;

        float m_travelled_distance;
        size_t m_direction_index;

        bool m_is_firing;
        bool m_is_launching_missile;

        Command m_fire_command, m_missile_command;
        sf::Time m_fire_count_down;
        int m_fire_rate_level;
};
