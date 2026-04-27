#pragma once

#include "resources/ResourceIdentifier.hpp"
#include <vector>

struct AircraftData {
    long long int hp;
    long long int speed;
    Textures::ID texture_id;
};

std::vector<AircraftData> initializeAircarftData();
