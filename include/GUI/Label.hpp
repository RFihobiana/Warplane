#pragma once

#include "GUI/Component.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include <string>
namespace GUI {
    class Label: public Component {
        public:
            typedef std::shared_ptr<Label> Ptr;

        public:
            Label(const FontHolder& font, const std::string& text_value = "");
            
            virtual bool is_selectable() const;

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            sf::Text m_text;
    };
}
