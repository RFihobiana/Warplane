#pragma once

#include "resources/ResourceIdentifier.hpp"
#include <vector>

struct AircraftData {
    float hp;
    float speed;
    Textures::ID texture_id;
};

std::vector<AircraftData> initializeAircarftData();
