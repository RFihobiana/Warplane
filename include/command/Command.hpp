#pragma once

#include "SceneNode.hpp"
#include <SFML/System/Time.hpp>
#include <functional>

struct Command {
    std::function<void(SceneNode& target, sf::Time& dt)> action;
    unsigned int category;
};
