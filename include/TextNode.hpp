#pragma once

#include "SceneNode.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class TextNode: public SceneNode {
    public:
        TextNode(const FontHolder& fonts, const std::string& value);

        void set_string(const std::string& value);
    
    private:
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Text m_text;
};
