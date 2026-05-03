#pragma once

#include "command/CommandQueue.hpp"
#include "entity/Entity.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Projectile: public Entity {
    public:
        enum Type {
            AlliedBullet,
            EnemyBullet,
            Missile,
            TypeCount
        };

    public:
        Projectile(const Type type, const TextureHolder& textures);

        void guide_towards(sf::Vector2f position);
        bool is_guided() const;

        virtual unsigned int get_category() const;
        virtual sf::FloatRect get_bounding_rect() const;
        long long int get_max_speed() const;
        float get_damage() const;

    private:
        virtual void update_current(sf::Time& dt, CommandQueue& command_queue);
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        Type m_type;
        sf::Sprite m_sprite;
        sf::Vector2f m_target_direction;
};
