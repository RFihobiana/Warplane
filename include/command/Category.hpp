#pragma once

namespace Category {
    enum Type {
        None            = 0,
        PlayerAircraft  = 1 << 0,
        AlliedAircraft  = 1 << 1,
        EnemyAircraft   = 1 << 2,
        Scene           = 1 << 3,

        AlliedProjectile    = 1 << 4,
        EnemyProjectile     = 1 << 5,

        Pickup              = 1 << 6,

        Aircraft            = PlayerAircraft | AlliedAircraft | EnemyAircraft,
        Projectile          = AlliedProjectile | EnemyProjectile,
    };
}
