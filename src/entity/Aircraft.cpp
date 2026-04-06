#include "entity/Aircraft.hpp"
#include "command/Category.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>

Textures::ID get_texture_id(const Aircraft::Type type) {
    switch (type) {
        case Aircraft::Eagle: return Textures::Eagle;
        case Aircraft::Raptor: return Textures::Raptor;
    }

    assert(false);
}

Aircraft::Aircraft(const Aircraft::Type type, const TextureHolder& textures)
: m_type(type) {
    const auto texture_id = get_texture_id(type);
    m_sprite.setTexture(textures.get(texture_id));
    center_origin(m_sprite);
}

void Aircraft::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

unsigned int Aircraft::get_category() const {
    switch (m_type) {
        case Eagle: return Category::PlayerAircraft;
        default:    return Category::EnemyAircraft;
    }
}