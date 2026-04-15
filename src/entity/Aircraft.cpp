#include "entity/Aircraft.hpp"
#include "command/Category.hpp"
#include "entity/DataTable.hpp"
#include "entity/Entity.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <vector>

namespace { const std::vector<AircraftData> Table = initializeAircarftData(); }

Aircraft::Aircraft(const Aircraft::Type type, const TextureHolder& textures)
: Entity(Table[type].hp)
, m_type(type) {
    m_sprite.setTexture(textures.get(Table[type].texture_id));
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