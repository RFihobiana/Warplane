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
#include <cmath>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace { const std::vector<AircraftData> Table = initialize_aircarft_data(); }

Aircraft::Aircraft(const Aircraft::Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[type].hp)
, m_type(type)
, m_travelled_distance(0.f)
, m_direction_index(0) {
    m_sprite.setTexture(textures.get(Table[type].texture_id));
    center_origin(m_sprite);
    
    // health
    std::unique_ptr<TextNode> health_node(new TextNode(fonts, std::to_string(Table[type].hp)));
    health_node->setPosition(0.f, 50.f);
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

    update_movement_pattern(dt);
}

void Aircraft::update_movement_pattern(sf::Time& dt) {
    const std::vector<Direction>& directions(Table[m_type].directions);
    
    if(directions.empty()) return; // Player have no direction

    float distance_to_travel = directions[m_direction_index].distance;
    if(distance_to_travel < m_travelled_distance) {
        m_direction_index = (m_direction_index + 1) % directions.size();
        m_travelled_distance = 0.f;
    }

    float radian = to_radian(directions[m_direction_index].angle + 90.f);
    float speed = Table[m_type].speed;
    set_velocity(speed * sf::Vector2f(std::cos(radian), std::sin(radian)));
    m_travelled_distance += speed * dt.asSeconds();
}

unsigned int Aircraft::get_category() const {
    switch (m_type) {
        case Eagle: return Category::PlayerAircraft;
        default:    return Category::EnemyAircraft;
    }
}