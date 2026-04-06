#pragma once

namespace Category {
    enum Type {
        None            = 0,
        PlayerAircraft  = 1 << 0,
        AlliedAircraft  = 1 << 1,
        EnemyAircraft   = 1 << 2,
        Scene           = 1 << 3,
    };
}
