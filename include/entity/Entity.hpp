#pragma once

#include "SceneNode.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Entity: public SceneNode {
    public:
        explicit Entity(const float hitpoints);
        void damage(const float points);
        void repair(const float points);
        void destroy();

        float get_hitpoints() const;
        bool is_destroyed() const;

        void set_velocity(const sf::Vector2f& velocity);
        void set_velocity(const float& vx, const float& vy);
        
        void accelerate(const sf::Vector2f& acceleration);
        void accelerate(const float& ax, const float& ay);

        sf::Vector2f get_velocity() const;
    
    protected:
        virtual void update_current(sf::Time& dt);
    
    private:
        float m_hitpoints;
        sf::Vector2f m_velocity;
};
