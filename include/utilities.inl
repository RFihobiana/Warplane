#pragma once

#include "utilities.hpp"
#include <SFML/Graphics.hpp>

template<typename T>
void center_origin(T& element) {
    const sf::FloatRect bounds(element.getLocalBounds());
    element.setOrigin(bounds.width / 2, bounds.height / 2);
}
