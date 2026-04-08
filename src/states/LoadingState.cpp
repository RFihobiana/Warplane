#include "states/LoadingState.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include "states/StateStack.hpp"
#include "utilities.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <sstream>

LoadingState::LoadingState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_loading_text("Loading Resources...", ctx.fonts->get(Fonts::main)) {
    sf::Vector2f view_size = ctx.window->getDefaultView().getSize();

    // Loading text
    center_origin(m_loading_text);
    m_loading_text.setPosition(view_size / 2.f);

    // Background
    m_progress_bar_bg.setFillColor(sf::Color::White);
    m_progress_bar_bg.setSize(sf::Vector2f(
        view_size.x - 20,
        20.f
    ));
    m_progress_bar_bg.setPosition(
        10.f,
        m_loading_text.getPosition().y + 40
    );

    m_progress_bar.setFillColor(sf::Color(0x98, 0xdc, 0x42, 0xda));
    m_progress_bar.setSize(sf::Vector2f(
        0.f,
        m_progress_bar_bg.getSize().y
    ));
    m_progress_bar.setPosition(m_progress_bar_bg.getPosition());

    set_completion(0.f);
    m_task.execute();
}

void LoadingState::set_completion(float percent) {
    if (percent > 1) percent = 1.f;

    m_progress_bar.setSize(sf::Vector2f(
        m_progress_bar_bg.getSize().x * percent,
        m_progress_bar.getSize().y
    ));
}

void LoadingState::draw() const {
    sf::RenderWindow& window = *get_context().window;

    window.draw(m_loading_text);
    window.draw(m_progress_bar_bg);
    window.draw(m_progress_bar);
}

bool LoadingState::handle_events(const sf::Event& event) {
    return true;
}

bool LoadingState::update(sf::Time& dt) {
    
    const float completion = m_task.get_completion();

    if(m_task.is_finished()) {
        request_pop();
        request_push(States::Game);
    } else set_completion(completion);

    std::stringstream loading_text;
    loading_text << "Loading Resources " << static_cast<int>(completion * 100) << "% ...";

    m_loading_text.setString(loading_text.str());

    return true;
}
