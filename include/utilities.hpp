#pragma once

#include "SceneNode.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

template<typename T>
void center_origin(T& element);

std::string to_string(const sf::Keyboard::Key key);

float to_radian(const float degree);
float to_degree(const float radian);

sf::Vector2f normalized(const sf::Vector2f& vector);

// Get distance between two scene node
float distance(const SceneNode& a, const SceneNode& b);

// A helper function: it work like distance**2
float nearest_scene(const SceneNode& a, const SceneNode& b);

#include "utilities.inl"