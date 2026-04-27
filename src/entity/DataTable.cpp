#include "entity/DataTable.hpp"
#include "entity/Aircraft.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <vector>

Direction::Direction(const float angle, const float distance)
    : angle(angle), distance(distance) {}

std::vector<AircraftData> initializeAircarftData() {
    std::vector<AircraftData> data(Aircraft::TypeCount);

    data[Aircraft::Eagle].hp = 100;
    data[Aircraft::Eagle].speed = 400;
    data[Aircraft::Eagle].texture_id = Textures::Eagle;
    
    data[Aircraft::Raptor].hp = 100;
    data[Aircraft::Raptor].speed = 150;
    data[Aircraft::Raptor].texture_id = Textures::Raptor;
    data[Aircraft::Raptor].directions.push_back(Direction(45.f, 80));
    data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 80 * 2));
    data[Aircraft::Raptor].directions.push_back(Direction(45.f, 80));
    
    data[Aircraft::Avenger].hp = 100;
    data[Aircraft::Avenger].speed = 100;
    data[Aircraft::Avenger].texture_id = Textures::Avenger;
    data[Aircraft::Avenger].directions.push_back(Direction(45.f, 50.f));
    data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
    data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 50.f * 2));
    data[Aircraft::Avenger].directions.push_back(Direction(0.f, 50.f));
    data[Aircraft::Avenger].directions.push_back(Direction(45.f, 50.f));

    return data;
}
