#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <string>
template<typename T>
void center_origin(T& element);

std::string to_string(const sf::Keyboard::Key key);

#include "utilities.inl"