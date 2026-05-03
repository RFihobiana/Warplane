#pragma once

#include "resources/ResourceIdentifier.hpp"
#include <vector>

struct Direction {
    Direction(const float angle, const float distance);

    float angle;
    float distance;
};

struct AircraftData {
    long long int           hp;
    long long int           speed;
    Textures::ID            texture_id;
    std::vector<Direction>  directions;
};

struct ProjectileData {
    float           damage;
    long long int   speed;
    Textures::ID    texture_id;
};


std::vector<AircraftData> initialize_aircarft_data();
std::vector<ProjectileData> initialize_projectile_data();
