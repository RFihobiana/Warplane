#pragma once

#include "Entity.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
class Aircraft: public Entity {
    public:
        typedef std::unique_ptr<Aircraft> Ptr;
        
        enum Type {
            Eagle,
            Raptor,
        };
    
    public:
        explicit Aircraft(const Type type, const TextureHolder& textures);

        void move_down(const bool is_pressed);
        void move_right(const bool is_pressed);
        void move_left(const bool is_pressed);
        void move_up(const bool is_pressed);
    
    private:
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void update_current(sf::Time& dt);
    
    private:
        Type m_type;
        sf::Sprite m_sprite;

        bool m_is_moving_up;
        bool m_is_moving_down;
        bool m_is_moving_right;
        bool m_is_moving_left;
};
