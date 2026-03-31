#pragma once

#include "entity/Entity.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class SpriteNode: public Entity {
    public:
        SpriteNode(const sf::Texture& texture);
    
    private:
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
    
    private:
        sf::Sprite m_sprite;
};
