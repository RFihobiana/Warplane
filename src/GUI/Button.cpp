#include "GUI/Button.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>

namespace GUI {
    
    Button::Button(
        const TextureHolder&    textures,
        const FontHolder&       fonts,
        const std::string&      text_value
    )
    : m_normal_texture(textures.get(Textures::ButtonNormal))
    , m_pressed_texture(textures.get(Textures::ButtonPressed))
    , m_selected_texture(textures.get(Textures::ButtonSelected))
    , m_text(text_value, fonts.get(Fonts::main))
    , m_sprite(m_normal_texture) {
        center_origin(m_text);
        center_origin(m_sprite);
    }

    bool Button::is_selectable() const { return true; }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
        target.draw(m_text, states);
    }
}
