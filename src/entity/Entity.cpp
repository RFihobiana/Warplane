#include "entity/Entity.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

void Entity::set_velocity(const sf::Vector2f& velocity) {
    m_velocity = velocity;
}

void Entity::set_velocity(const float& vx, const float& vy) {
    m_velocity.x = vx;
    m_velocity.y = vy;
}

void Entity::update_current(sf::Time& dt) {
    move(m_velocity);
}
