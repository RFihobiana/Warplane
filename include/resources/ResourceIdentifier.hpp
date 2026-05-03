#pragma once

#include "resources/ResourceHolder.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
namespace Textures {
    enum ID {

        Landscape,

        // Aircraft
        Eagle,
        Raptor,
        Avenger,

        // Guns
        Bullet,
        Missile,

        // Pickup
        FireRate,
        HealthRefill,
        MissileRefill,

        // Buttons
        ButtonNormal,
        ButtonPressed,
        ButtonSelected,
    };
}

namespace Fonts {
    enum ID {
        main,
        Hanalei,
    };
}

typedef ResourceHolder<Textures::ID, sf::Texture> TextureHolder;
typedef ResourceHolder<Fonts::ID, sf::Font> FontHolder;
