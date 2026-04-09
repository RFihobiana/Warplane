#include "GUI/Button.hpp"
#include "GUI/Component.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
namespace GUI {
    Button::Button(TextureHolder& textures)
    : m_normal_texture(textures.get(Textures::ButtonNormal))
    , m_active_texture(textures.get(Textures::ButtonPressed))
    , m_selected_texture(textures.get(Textures::ButtonSelected))
    , m_sprite(m_normal_texture) {}

    bool Button::is_selectable() const {
        return true;
    }

    void Button::select() {
        Component::select();
        m_sprite.setTexture(m_selected_texture);
    }

    void Button::handle_events(const sf::Event& event) {}

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_sprite, states);
    }
}
