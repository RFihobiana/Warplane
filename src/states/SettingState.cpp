#include "states/SettingState.hpp"
#include "GUI/Button.hpp"
#include "states/State.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <string>

SettingState::SettingState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_backgrounds(ctx.window->getDefaultView().getSize()) {
    m_backgrounds.setFillColor(sf::Color(0x8e, 0x7e, 0x7e));

    // Buttons
    add_button("Move Left", 0.f);
    add_button("Move Right", 50.f);
    add_button("Move Up", 100.f);
    add_button("Move Down", 150.f);
    add_button("Player Pos", 200.f);

    m_GUIContainer.setPosition(ctx.window->getDefaultView().getSize() / 2.f);
}

void SettingState::add_button(const std::string& text, const float y) {
    const Context& ctx = get_context();
    GUI::Button::Ptr btn(std::make_shared<GUI::Button>(*ctx.textures, *ctx.fonts, text));
    btn->setPosition(0.f, y);
    btn->set_toggle(true);
    m_GUIContainer.pack(btn);
}

void SettingState::draw() const {
    sf::RenderWindow& window = *get_context().window;
    
    window.draw(m_backgrounds);
    window.draw(m_GUIContainer);
}

bool SettingState::update(sf::Time& dt) {
    return true;
}

bool SettingState::handle_events(const sf::Event& event) {
    return true;
}
