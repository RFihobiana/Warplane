#include "states/GameState.hpp"
#include "command/CommandQueue.hpp"
#include "entity/Player.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/State.hpp"
#include "states/StateIdentification.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

GameState::GameState(StateStack& stack, Context& ctx)
: State(stack, ctx)
, m_world(*ctx.window, *ctx.textures) {
    load_resources();
}

void GameState::load_resources() {
    // Fonts
    FontHolder& fonts = *get_context().fonts;
    if(!fonts.has(Fonts::main)) fonts.load(Fonts::main, "assets/fonts/Sansation.ttf");
    
    // Textures
    TextureHolder& textures = *get_context().textures;

    if(!textures.has(Textures::Landscape)) textures.load(Textures::Landscape, "assets/images/Desert.png");
    if(!textures.has(Textures::Eagle)) textures.load(Textures::Eagle, "assets/images/Eagle.png");
    if(!textures.has(Textures::Raptor)) textures.load(Textures::Raptor, "assets/images/Raptor.png");
}

bool GameState::handle_events(const sf::Event& event) {

    CommandQueue& commands = m_world.get_command_queue();
    
    Player& player = *get_context().player;
    player.handle_event(event, commands);

    // Pause
    if(event.type == sf::Event::KeyReleased) {
        if(event.key.code == sf::Keyboard::Escape) {
            request_push(States::Pause);
        }
    } else if(event.type == sf::Event::LostFocus) {
        // Pause automatically
        request_push(States::Pause);
    }

    return true;
}

bool GameState::update(sf::Time& dt) {
    m_world.update(dt);

    CommandQueue& commands = m_world.get_command_queue();
    get_context().player->handle_realtime_event(commands);

    return true;
}

void GameState::draw() const {
    m_world.draw();
}