#include "entity/DataTable.hpp"
#include "entity/Aircraft.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <vector>

std::vector<AircraftData> initializeAircarftData() {
    std::vector<AircraftData> data(Aircraft::TypeCount);

    data[Aircraft::Eagle].hp = 100.f;
    data[Aircraft::Eagle].speed = 400.f;
    data[Aircraft::Eagle].texture_id = Textures::Eagle;
    
    data[Aircraft::Raptor].hp = 100.f;
    data[Aircraft::Raptor].speed = 150.f;
    data[Aircraft::Raptor].texture_id = Textures::Raptor;
    
    data[Aircraft::Avenger].hp = 100.f;
    data[Aircraft::Avenger].speed = 100.f;
    data[Aircraft::Avenger].texture_id = Textures::Avenger;

    return data;
}
