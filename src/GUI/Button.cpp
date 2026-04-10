#include "GUI/Button.hpp"
#include "GUI/Component.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

namespace GUI {
    
    Button::Button(
        const TextureHolder&    textures,
        const FontHolder&       fonts,
        const std::string&      text_value
    )
    : m_is_toggled(false)
    , m_normal_texture(textures.get(Textures::ButtonNormal))
    , m_pressed_texture(textures.get(Textures::ButtonPressed))
    , m_selected_texture(textures.get(Textures::ButtonSelected))
    , m_text(text_value, fonts.get(Fonts::main))
    , m_sprite(m_normal_texture) {
        center_origin(m_text);
        center_origin(m_sprite);
        m_text.move(0.f, -6.5f);
    }

    void Button::set_callback(Button::Fn cb) { m_callback = cb; }

    bool Button::is_selectable() const { return true; }

    void Button::select() {
        Component::select();
        m_sprite.setTexture(m_selected_texture);
    }

    void Button::deselect() {
        Component::deselect();
        m_sprite.setTexture(m_normal_texture);
    }

    void Button::activate() {
        Component::activate();
        if(m_is_toggled) m_sprite.setTexture(m_pressed_texture);
        if(m_callback) m_callback();
        if(!m_is_toggled) deactivate();
    }

    void Button::deactivate() {
        Component::deactivate();
        if(m_is_toggled) {
            if(is_selected()) m_sprite.setTexture(m_pressed_texture);
            else m_sprite.setTexture(m_normal_texture);
        }
    }

    void Button::set_toggle(const bool toggled) { m_is_toggled = toggled; }

    void Button::handle_events(const sf::Event& event) {
    }

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
        target.draw(m_text, states);
    }
}
