#include "entity/Player.hpp"
#include "command/Category.hpp"
#include "command/Command.hpp"
#include "entity/Aircraft.hpp"
#include "SceneNode.hpp"
#include "command/CommandQueue.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

struct AircraftMover {
    AircraftMover(const float vx, const float vy): velocity(vx, vy) {}

    void operator() (Aircraft& aircraft, sf::Time& dt) const {
        aircraft.accelerate(velocity * dt.asSeconds());
    }

    const sf::Vector2f velocity;
};

Player::Player() {
}

void Player::handle_event(const sf::Event& event, CommandQueue& commands) {
}
void Player::handle_realtime_event(CommandQueue& commands) {
    const float speed = 2.5f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        Command move_up {
            .action     = derivated<Aircraft>(AircraftMover(0.f, -speed)),
            .category   = Category::PlayerAircraft
        };

        commands.push_back(move_up);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Command move_down {
            .action     = derivated<Aircraft>(AircraftMover(0.f, speed)),
            .category   = Category::PlayerAircraft
        };
        commands.push_back(move_down);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Command move_left {
            .action = derivated<Aircraft>(AircraftMover(-speed, 0.f)),
            .category = Category::PlayerAircraft
        };
        commands.push_back(move_left);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Command move_right {
            .action     = derivated<Aircraft>(AircraftMover(speed, 0.f)),
            .category   = Category::PlayerAircraft
        };
        commands.push_back(move_right);
    }

}
