#pragma once

#include "SceneNode.hpp"
#include "command/Category.hpp"
#include <SFML/System/Time.hpp>
#include <functional>

struct Command {
    std::function<void(SceneNode& target, sf::Time& dt)> action;
    unsigned int category;

    Command(const std::function<void(SceneNode& target, sf::Time& dt)>& action, const unsigned int& category = Category::None);
};
