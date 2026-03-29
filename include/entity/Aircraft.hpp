#pragma once

#include "Entity.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Aircraft: public Entity {
    public:
        enum Type {
            Eagle,
            Raptor,
        };
    
    public:
        explicit Aircraft(const Type type, const TextureHolder& textures);
    
    private:
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
    
    private:
        Type m_type;
        sf::Sprite m_sprite;
};
