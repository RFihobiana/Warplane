#pragma once

#include "SceneNode.hpp"
#include "command/Category.hpp"
#include <SFML/System/Time.hpp>
#include <cassert>
#include <functional>

struct Command {
    std::function<void(SceneNode& target, sf::Time& dt)> action;
    unsigned int category = Category::None;
};

template<typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time&)> derivated(Function fn) {
    return [fn] (SceneNode& node, sf::Time& dt) {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        fn(static_cast<GameObject&>(node), dt);
    };
}

