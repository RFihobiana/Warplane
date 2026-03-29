#pragma once

#include "Entity.hpp"
class Aircraft: public Entity {
    public:
        enum Type {
            Eagle,
            Raptor,
        };
    
    public:
        explicit Aircraft(const Type type);
    
    private:
        Type m_type;
};
