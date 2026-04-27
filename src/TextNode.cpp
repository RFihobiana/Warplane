#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <TextNode.hpp>
#include <string>

TextNode::TextNode(const FontHolder& fonts, const std::string& value)
    : m_text(value, fonts.get(Fonts::main)) {
        center_origin(m_text);
    }

void TextNode::set_string(const std::string& value) {
    m_text.setString(value);
    center_origin(m_text);
}

void TextNode::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_text, states);
}

