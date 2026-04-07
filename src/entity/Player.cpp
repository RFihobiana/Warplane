#include "entity/Player.hpp"
#include "command/Category.hpp"
#include "command/Command.hpp"
#include "entity/Aircraft.hpp"
#include "SceneNode.hpp"
#include "command/CommandQueue.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <iostream>
#include <utility>

struct AircraftMover {
    AircraftMover(const float vx, const float vy): velocity(vx, vy) {}

    void operator() (Aircraft& aircraft, sf::Time& dt) const {
        aircraft.accelerate(velocity * dt.asSeconds());
    }

    const sf::Vector2f velocity;
};

Player::Player() {
    const float player_speed = 200.f;

    m_key_binding[sf::Keyboard::W] = MoveUp;
    m_key_binding[sf::Keyboard::S] = MoveDown;
    m_key_binding[sf::Keyboard::A] = MoveLeft;
    m_key_binding[sf::Keyboard::D] = MoveRight;
    m_key_binding[sf::Keyboard::P] = ShowPosition;

    m_action_binding[MoveLeft].action = derivated<Aircraft>(AircraftMover(-player_speed, 0.f));
    m_action_binding[MoveRight].action = derivated<Aircraft>(AircraftMover(player_speed, 0.f));
    m_action_binding[MoveUp].action = derivated<Aircraft>(AircraftMover(0.f, -player_speed));
    m_action_binding[MoveDown].action = derivated<Aircraft>(AircraftMover(0.f, player_speed));
    m_action_binding[ShowPosition].action = derivated<Aircraft>([](Aircraft& aircraft, sf::Time&) {
        const sf::Vector2f pos = aircraft.getPosition();
        std::cout
            << "P: ("
            << pos.x << ", " << pos.y
            << ")"
            << std::endl;
    });

    for(auto& pair: m_action_binding) pair.second.category = Category::PlayerAircraft;
}

void Player::handle_event(const sf::Event& event, CommandQueue& commands) {
    if(event.type == sf::Event::KeyReleased) {
        for(const auto& pair: m_key_binding) {
            if(!is_realtime_action(pair.second) && event.key.code == pair.first) {
                commands.push_back(m_action_binding[pair.second]);
            }
        }
    }
}

void Player::handle_realtime_event(CommandQueue& commands) {
    for(const auto& pair: m_key_binding) {
        if(is_realtime_action(pair.second) && sf::Keyboard::isKeyPressed(pair.first)) {
            commands.push_back(m_action_binding[pair.second]);
        }
    }
}

void Player::assign_key(const sf::Keyboard::Key& key, const Action& action) {
    m_key_binding[key] = action;
}

sf::Keyboard::Key Player::get_assigned_key(const Action& action) const {
    auto iter = std::find_if(m_key_binding.begin(), m_key_binding.end(), [&action](std::pair<sf::Keyboard::Key, Action> pair) {
        return pair.second == action;
    });

    if(iter == m_key_binding.end()) return sf::Keyboard::Unknown;
    return iter->first;
}

bool Player::is_realtime_action(const Action& action) {
    switch (action) {
        case MoveLeft:
        case MoveRight:
        case MoveUp:
        case MoveDown:
            return true;
        
        default: return false;
    }
}
