#include "states/SettingState.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "entity/Player.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>
#include <memory>
#include <string>

SettingState::SettingState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_backgrounds(ctx.window->getDefaultView().getSize()) {
    m_backgrounds.setFillColor(sf::Color(0x8e, 0x7e, 0x7e));

    // Buttons
    add_button_label(Player::MoveUp, "Move Up", 0.f);
    add_button_label(Player::MoveDown, "Move Down", 50.f);
    add_button_label(Player::MoveRight, "Move Right", 100.f);
    add_button_label(Player::MoveLeft, "Move Left", 150.f);
    add_button_label(Player::ShowPosition, "Player Pos", 200.f);
    add_button_label(Player::Fire, "Fire", 250.f);
    add_button_label(Player::LaunchMissile, "Launch Missile", 300.f);

    // back btn
    GUI::Button::Ptr back(std::make_shared<GUI::Button>(*ctx.textures, *ctx.fonts, "Back"));
    back->setPosition(
        m_button_binding[Player::ActionCount - 1]->getPosition() +
        sf::Vector2f(0.f, 250.f));
    back->set_callback([this]() { 
        request_pop();
        request_push(States::MainMenu);
    });
    m_GUIContainer.pack(back);

    m_GUIContainer.setPosition(
        ctx.window->getDefaultView().getSize().x * 0.50f,
        ctx.window->getDefaultView().getSize().y * 0.20f
    );
}

void SettingState::add_button_label(const Player::Action action, const std::string& text, const float y) {
    const Context& ctx = get_context();
    GUI::Button::Ptr btn(std::make_shared<GUI::Button>(*ctx.textures, *ctx.fonts, text));
    btn->setPosition(0.f, y);
    btn->set_toggle(true);
    m_button_binding[action] = btn;

    GUI::Label::Ptr label(std::make_shared<GUI::Label>(*ctx.fonts, to_string(ctx.player->get_assigned_key(action))));
    label->setPosition(150.f, y - 20);
    m_label_binding[action] = label;

    m_GUIContainer.pack(m_button_binding[action]);
    m_GUIContainer.pack(m_label_binding[action]);
}

void SettingState::update_labels() {
    for(size_t action = 0; action < Player::ActionCount; action++) {
        m_label_binding[action]->set_text(
            to_string(
                get_context().player->get_assigned_key(static_cast<Player::Action>(action))
            )
        );
    }
}

void SettingState::draw() const {
    sf::RenderWindow& window = *get_context().window;
    
    window.draw(m_backgrounds);
    window.draw(m_GUIContainer);
}

bool SettingState::update(sf::Time& dt) { return true; }

bool SettingState::handle_events(const sf::Event& event) {
    bool is_key_binding = false;

    for(size_t action = 0; action < Player::ActionCount; action++) {
        if(m_button_binding[action]->is_active()) {
            is_key_binding = true;
            if(event.type == sf::Event::KeyReleased) {
                get_context().player->assign_key(event.key.code, static_cast<Player::Action>(action));
                m_button_binding[action]->deactivate();
            }
            break;
        }
    }

    if(is_key_binding) {
        update_labels();
    } else m_GUIContainer.handle_events(event);
    return false;
}
