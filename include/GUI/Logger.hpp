#pragma once

#include "GUI/Component.hpp"
#include "GUI/Label.hpp"
#include "log/Log.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <string>
#include <vector>

namespace GUI {
    class Logger: public Log, public Component {
        public:
            typedef std::shared_ptr<Logger> Ptr;

        public:
            Logger(TextureHolder& textures, FontHolder& fonts);

            virtual bool is_selectable() const;
            virtual void add(const std::string& log);

            virtual void handle_events(const sf::Event& event);

            void set_bg_size(const sf::Vector2f size);
            void set_bg_size(const float width, const float height);

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            const TextureHolder&    m_textures;
            const FontHolder&       m_fonts;
            std::vector<Label::Ptr> m_labels;
            sf::RectangleShape      m_bg_rect;
            bool                    m_hide;
    };
}
