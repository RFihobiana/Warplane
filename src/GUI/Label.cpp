#include "GUI/Label.hpp"
#include "GUI/Component.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

namespace GUI {
    Label::Label(const FontHolder& fonts, const std::string& text_value)
    : Component()
    , m_text(text_value, fonts.get(Fonts::main)) {
        center_origin(m_text);
    }

    bool Label::is_selectable() const { return false; }

    void Label::handle_events(const sf::Event& event) {}

    void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(m_text, states);
    }
}
