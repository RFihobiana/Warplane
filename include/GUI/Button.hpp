#pragma once

#include "GUI/Component.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <functional>
#include <memory>
#include <string>

namespace GUI {
    class Button: public Component {
        public:
            typedef std::function<void()> Fn;
            typedef std::shared_ptr<Button> Ptr;

        public:
            Button(
                const TextureHolder& textures,
                const FontHolder& fonts,
                const std::string& text_value = ""
            );

            void set_callback(Fn cb);

            virtual bool is_selectable() const;
            virtual void select();
            virtual void deselect();

            virtual void activate();
            virtual void deactivate();
            void set_toggle(const bool toggled);

            virtual void handle_events(const sf::Event& event);

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            bool m_is_toggled;

            const sf::Texture& m_normal_texture;
            const sf::Texture& m_pressed_texture;
            const sf::Texture& m_selected_texture;

            sf::Text m_text;
            sf::Sprite m_sprite;
            
            Fn m_callback;
    };
}
