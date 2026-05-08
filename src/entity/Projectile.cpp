#include "entity/Projectile.hpp"
#include "command/Category.hpp"
#include "entity/DataTable.hpp"
#include "entity/Entity.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <vector>

namespace { const std::vector<ProjectileData> Table = initialize_projectile_data(); }

Projectile::Projectile(const Type type, const TextureHolder& textures)
: Entity(1)
, m_type(type)
, m_sprite(textures.get(Table[type].texture_id)) {
    set_velocity(0.f, (m_type == EnemyBullet)? Table[m_type].speed : -Table[m_type].speed);
    center_origin(m_sprite);
}

void Projectile::guide_towards(sf::Vector2f position) {}

bool Projectile::is_guided() const {
    return m_type == Missile;
}

unsigned int Projectile::get_category() const {
    switch (m_type) {
        case AlliedBullet: return Category::AlliedProjectile;
        case EnemyBullet: return Category::EnemyProjectile;
        
        default: return Category::Projectile;
    }
}

sf::FloatRect Projectile::get_bounding_rect() const {
    return get_world_transform().transformRect(m_sprite.getGlobalBounds());
}

long long int Projectile::get_max_speed() const { return Table[m_type].speed; }

float Projectile::get_damage() const { return Table[m_type].damage; }

void Projectile::update_current(sf::Time& dt, CommandQueue& commands) {
    Entity::update_current(dt, commands);
}

void Projectile::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}


