#include "entity/DataTable.hpp"
#include "entity/Aircraft.hpp"
#include "entity/Projectile.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <vector>

Direction::Direction(const float angle, const float distance)
    : angle(angle), distance(distance) {}

std::vector<AircraftData> initialize_aircarft_data() {
    std::vector<AircraftData> data(Aircraft::TypeCount);

    data[Aircraft::Eagle].hp = 100;
    data[Aircraft::Eagle].speed = 400;
    data[Aircraft::Eagle].texture_id = Textures::Eagle;
    
    data[Aircraft::Raptor].hp = 10;
    data[Aircraft::Raptor].speed = 100;
    data[Aircraft::Raptor].texture_id = Textures::Raptor;
    data[Aircraft::Raptor].directions.push_back(Direction(45.f, 80));
    data[Aircraft::Raptor].directions.push_back(Direction(-45.f, 80 * 2));
    data[Aircraft::Raptor].directions.push_back(Direction(45.f, 80));
    
    data[Aircraft::Avenger].hp = 40;
    data[Aircraft::Avenger].speed = 30;
    data[Aircraft::Avenger].texture_id = Textures::Avenger;
    data[Aircraft::Avenger].directions.push_back(Direction(45.f, 60.f));
    data[Aircraft::Avenger].directions.push_back(Direction(0.f, 60.f));
    data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 60.f * 2));
    data[Aircraft::Avenger].directions.push_back(Direction(0.f, 60.f));
    data[Aircraft::Avenger].directions.push_back(Direction(45.f, 60.f));

    return data;
}

std::vector<ProjectileData> initialize_projectile_data() {
    std::vector<ProjectileData> data(Projectile::TypeCount);
    
    data[Projectile::AlliedBullet].damage = 10.f;
    data[Projectile::AlliedBullet].speed = 300;
    data[Projectile::AlliedBullet].texture_id = Textures::Bullet;
    
    data[Projectile::EnemyBullet].damage = 10.f;
    data[Projectile::EnemyBullet].speed = 300;
    data[Projectile::EnemyBullet].texture_id = Textures::Bullet;

    data[Projectile::Missile].damage = 200.f;
    data[Projectile::Missile].speed = 150;
    data[Projectile::Missile].texture_id = Textures::Missile;

    return data;
}
