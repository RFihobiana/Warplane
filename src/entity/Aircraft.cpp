#include "entity/Aircraft.hpp"
#include "TextNode.hpp"
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
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace { const std::vector<AircraftData> Table = initializeAircarftData(); }

Aircraft::Aircraft(const Aircraft::Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].hp)
, m_type(type) {
    m_sprite.setTexture(textures.get(Table[type].texture_id));
    center_origin(m_sprite);
    
    // health
    std::unique_ptr<TextNode> health_node(new TextNode(fonts, std::to_string(Table[type].hp)));
    health_node->setPosition(0.f, 40.f);
    m_health_display = health_node.get();
    attach_child(std::move(health_node));
}

void Aircraft::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void Aircraft::update_current(sf::Time& dt) {
    Entity::update_current(dt);
    m_health_display->set_string(std::to_string(get_hitpoints()) + " HP");
    m_health_display->setRotation(-getRotation());
}

unsigned int Aircraft::get_category() const {
    switch (m_type) {
        case Eagle: return Category::PlayerAircraft;
        default:    return Category::EnemyAircraft;
    }
}