#pragma once

#include "GUI/Component.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace GUI {
    class Button: public Component {
        public:
            Button(
                const TextureHolder& textures,
                const FontHolder& fonts,
                const std::string& text_value = ""
            );

            virtual bool is_selectable() const;
            virtual void select();
            virtual void deselect();

            virtual void handle_events(const sf::Event& event);

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            const sf::Texture& m_normal_texture;
            const sf::Texture& m_pressed_texture;
            const sf::Texture& m_selected_texture;

            sf::Text m_text;
            sf::Sprite m_sprite;
    };
}
