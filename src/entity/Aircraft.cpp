#include "entity/Aircraft.hpp"
#include "SceneNode.hpp"
#include "TextNode.hpp"
#include "command/Category.hpp"
#include "command/CommandQueue.hpp"
#include "entity/DataTable.hpp"
#include "entity/Entity.hpp"
#include "entity/Projectile.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/Rect.hpp>
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
, m_direction_index(0)
, m_is_firing(false)
, m_is_launching_missile(false)
, m_fire_count_down(sf::Time::Zero)
, m_fire_rate_level(1)
, m_spread_level(1) {
    m_sprite.setTexture(textures.get(Table[type].texture_id));
    center_origin(m_sprite);
    
    // health
    std::unique_ptr<TextNode> health_node(new TextNode(fonts, std::to_string(Table[type].hp)));
    health_node->setPosition(0.f, 50.f);
    m_health_display = health_node.get();
    attach_child(std::move(health_node));

    m_fire_command.category = Category::SceneAirLayer;
    m_fire_command.action = [this, &textures] (SceneNode& layer, sf::Time& dt) {
        create_bullets(layer, textures);
    };

    m_missile_command.category = Category::SceneAirLayer;
    m_missile_command.action = [this, &textures] (SceneNode& layer, sf::Time& dt) {
        create_projectile(layer, textures, Projectile::Missile, 0.f, 0.f);
    };
}

void Aircraft::fire() {
    m_is_firing = true;
}

void Aircraft::launch_missile() {
    m_is_launching_missile = true;
}

void Aircraft::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void Aircraft::update_current(sf::Time& dt, CommandQueue& commands) {
    Entity::update_current(dt, commands);
    m_health_display->set_string(std::to_string(get_hitpoints()) + " HP");
    m_health_display->setRotation(-getRotation());

    update_movement_pattern(dt);

    if(!is_allied()) fire();
    
    check_projectile_launch(dt, commands);
}

void Aircraft::update_movement_pattern(sf::Time& dt) {
    const std::vector<Direction>& directions(Table[m_type].directions);
    
    if(directions.empty()) return; // Player have no direction

    const float& distance_to_travel = directions[m_direction_index].distance;
    if(distance_to_travel < m_travelled_distance) {
        m_direction_index = (m_direction_index + 1) % directions.size();
        m_travelled_distance = 0.f;
    }

    const float radian = to_radian(directions[m_direction_index].angle + 90.f);
    float speed = Table[m_type].speed;
    set_velocity(speed * sf::Vector2f(std::cos(radian), std::sin(radian)));
    m_travelled_distance += speed * dt.asSeconds();
}

void Aircraft::check_projectile_launch(sf::Time& dt, CommandQueue& commands) {
    // Bullet
    if(m_is_firing && m_fire_count_down <= sf::Time::Zero) {
        commands.push_back(m_fire_command);
        m_is_firing = false;
        m_fire_count_down += sf::seconds(1.f / (m_fire_rate_level + 1));
    } else if (m_fire_count_down > sf::Time::Zero) {
        m_fire_count_down -= dt;
    }

    // Missile
    if(m_is_launching_missile) {
        m_is_launching_missile = false;
        commands.push_back(m_missile_command);
    }
}

void Aircraft::create_bullets(SceneNode& layer, const TextureHolder& textures) {
    Projectile::Type type = is_allied()? Projectile::AlliedBullet : Projectile::EnemyBullet;

    switch (m_spread_level) {
        case 1:
            create_projectile(layer, textures, type, 0.f, 0.5f);
            break;
        
        case 2:
            create_projectile(layer, textures, type, -0.30f, 0.30f);
            create_projectile(layer, textures, type, 0.30f, 0.30f);
            break;

        default:
            // Max spread = 3
            create_projectile(layer, textures, type, -0.5f, 0.30f);
            create_projectile(layer, textures, type, 0.f, 0.5f);
            create_projectile(layer, textures, type, 0.5f, 0.30f);
            break ;
    }
}

void Aircraft::create_projectile(
    SceneNode& layer,
    const TextureHolder& textures,
    const Projectile::Type type,
    const float relx,
    const float rely
) {
    std::unique_ptr<Projectile> projectile(new Projectile(type, textures));
    const sf::FloatRect global_bounds = m_sprite.getGlobalBounds();
    const sf::Vector2f velocity(0.f, projectile->get_max_speed());
    const float sign = is_allied() ? -1.0f : +1.f;

    projectile->setPosition(get_world_position() + sf::Vector2f(relx * global_bounds.width, -rely * global_bounds.height));
    projectile->set_velocity(velocity * sign);
    layer.attach_child(std::move(projectile));
}

bool Aircraft::is_allied() const {
    return m_type == Eagle;
}

unsigned int Aircraft::get_category() const {
    switch (m_type) {
        case Eagle: return Category::PlayerAircraft;
        default:    return Category::EnemyAircraft;
    }
}