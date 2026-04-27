#pragma once

#include "Entity.hpp"
#include "TextNode.hpp"
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

        virtual unsigned int get_category() const;
    
    private:
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
        
        virtual void update_current(sf::Time& dt);
        void update_movement_pattern(sf::Time& dt);
    
    private:
        Type m_type;
        sf::Sprite m_sprite;
        TextNode* m_health_display;

        float m_travelled_distance;
        size_t m_direction_index;
};
