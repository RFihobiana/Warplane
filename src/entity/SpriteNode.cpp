#include "entity/SpriteNode.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

SpriteNode::SpriteNode(const sf::Texture& texture)
: m_sprite(texture) {
    center_origin(m_sprite);
}

void SpriteNode::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
