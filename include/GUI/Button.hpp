#pragma once

#include "GUI/Component.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
namespace GUI {

    class Button: public Component {
        public:
            Button(TextureHolder& textures);

            virtual bool is_selectable() const;
            virtual void select();
            
            virtual void handle_events(const sf::Event& event);
        
        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            sf::Texture& m_normal_texture;
            sf::Texture& m_active_texture;
            sf::Texture& m_selected_texture;

            sf::Sprite m_sprite;
    };

}
