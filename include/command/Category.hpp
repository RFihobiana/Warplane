#pragma once

namespace Category {
    enum Type {
        None            = 0,
        PlayerAircraft  = 1 << 0,
        AlliedAircraft  = 1 << 1,
        EnemyAircraft   = 1 << 2,
        
        Scene           = 1 << 3,
        SceneAirLayer   = 1 << 4,

        AlliedProjectile    = 1 << 5,
        EnemyProjectile     = 1 << 6,

        Pickup              = 1 << 7,

        Aircraft            = PlayerAircraft | AlliedAircraft | EnemyAircraft,
        Projectile          = AlliedProjectile | EnemyProjectile,
    };
}
