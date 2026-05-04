#include "entity/Entity.hpp"
#include "command/CommandQueue.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

Entity::Entity(const long long int hitpoints)
: m_hitpoints(hitpoints) {}

void Entity::damage(const long long int hp) {
    m_hitpoints -= hp;
}

void Entity::destroy() {
    m_hitpoints = 0.f;
}

void Entity::repair(const long long int hp) {
    m_hitpoints += hp;
}

long long int Entity::get_hitpoints() const {
    return m_hitpoints;
}

bool Entity::is_destroyed() const {
    return m_hitpoints >= 0.f;
}

void Entity::set_velocity(const sf::Vector2f& velocity) {
    m_velocity = velocity;
}

void Entity::set_velocity(const float& vx, const float& vy) {
    m_velocity.x = vx;
    m_velocity.y = vy;
}

void Entity::accelerate(const sf::Vector2f& acceleration) {
    m_velocity += acceleration;
}

void Entity::accelerate(const float& ax, const float& ay) {
    m_velocity.x += ax;
    m_velocity.y += ay;
}

sf::Vector2f Entity::get_velocity() const { return m_velocity; }

void Entity::update_current(sf::Time& dt, CommandQueue& commands) {
    move(m_velocity * dt.asSeconds());
}
