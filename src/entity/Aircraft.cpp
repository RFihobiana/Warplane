#include "entity/Aircraft.hpp"
#include "entity/Entity.hpp"
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

Aircraft::Aircraft(const Aircraft::Type type, const TextureHolder& textures): m_type(type) {
    const auto texture_id = get_texture_id(type);
    m_sprite.setTexture(textures.get(texture_id));
    center_origin(m_sprite);
}

void Aircraft::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void Aircraft::update_current(sf::Time& dt) {
    const float speed = 100.f;
    sf::Vector2f velocity(0.f,  -100.f);

    if(m_is_moving_up)     velocity.y -= speed;
    if(m_is_moving_down)   velocity.y += speed;
    if(m_is_moving_left)   velocity.x -= speed;
    if(m_is_moving_right)  velocity.x += speed;

    set_velocity(velocity * dt.asSeconds());

    Entity::update_current(dt);
}

void Aircraft::move_down(const bool is_pressed) {
    m_is_moving_down = is_pressed;
}

void Aircraft::move_right(const bool is_pressed) {
    m_is_moving_right = is_pressed;
}

void Aircraft::move_left(const bool is_pressed) {
    m_is_moving_left = is_pressed;
}

void Aircraft::move_up(const bool is_pressed) {
    m_is_moving_up = is_pressed;
}