#pragma once

#include "SceneNode.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Entity: public SceneNode {
    public:
        void set_velocity(const sf::Vector2f& velocity);
        void set_velocity(const float& vx, const float& vy);
        
        void accelerate(const sf::Vector2f& acceleration);

        sf::Vector2f get_velocity() const;
    
    protected:
        virtual void update_current(sf::Time& dt);
    
    private:
        sf::Vector2f m_velocity;
};
