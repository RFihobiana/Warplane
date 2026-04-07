#include "World.hpp"
#include "SceneNode.hpp"
#include "command/CommandQueue.hpp"
#include "entity/Aircraft.hpp"
#include "entity/SpriteNode.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>
#include <utility>

World::World(sf::RenderWindow& window, TextureHolder& textures)
: m_window(window)
, m_textures(textures)

, m_view(window.getDefaultView())
, m_world_bound(
    0.f,
    0.f,
    m_view.getSize().x,
    50000.f
)
, m_scroll_speed(0.f, -100.f)
, m_spawn_player(
    m_world_bound.left + m_world_bound.width / 2,
    m_world_bound.top + m_world_bound.height - m_view.getSize().y / 2
) {
    m_view.setCenter(m_spawn_player);
    load_resources();
    build();
}

void World::load_resources() {
    // Textures
    m_textures.load(Textures::Eagle, "./assets/images/Eagle.png");
    m_textures.load(Textures::Raptor, "./assets/images/Raptor.png");
    m_textures.load(Textures::Landscape, "./assets/images/Desert.png");
}

void World::build() {
    // Create Layers
    for(size_t i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer(new SceneNode());
        m_layers[i] = layer.get();
        m_graph.attach_child(std::move(layer));
    }

    // Create Background
    sf::Texture& landscape_texture(m_textures.get(Textures::Landscape));
    sf::IntRect bounds(0, 0, landscape_texture.getSize().x, m_world_bound.height);
    landscape_texture.setRepeated(true);
    
    SpriteNode::Ptr background(new SpriteNode(m_textures.get(Textures::Landscape), bounds));
    
    // Scale the background as the View itself
    auto view_size = m_view.getSize();
    auto texture_size = landscape_texture.getSize();
    background->setScale(sf::Vector2f(
        view_size.x / texture_size.x,
        view_size.y / texture_size.y
    ));
    background->setPosition(m_spawn_player);
    m_layers[Background]->attach_child(std::move(background));

    // Create Aircraft
    std::unique_ptr<Aircraft> aircraft(new Aircraft(Aircraft::Eagle, m_textures));
    aircraft->setPosition(m_spawn_player);
    aircraft->set_velocity(m_scroll_speed);
    m_player = aircraft.get();
    m_layers[Air]->attach_child(std::move(aircraft));
    
    // Player escort
    std::unique_ptr<Aircraft> left_escort(new Aircraft(Aircraft::Raptor, m_textures));
    left_escort->setPosition(-60.f, 80.f);
    m_player->attach_child(std::move(left_escort));

    std::unique_ptr<Aircraft> right_escort(new Aircraft(Aircraft::Raptor, m_textures));
    right_escort->setPosition(60.f, 80.f);
    m_player->attach_child(std::move(right_escort));
}

void World::update(sf::Time& dt) {
    m_view.move(m_scroll_speed * dt.asSeconds());
    m_player->set_velocity(0.f, 0.f);

    // Propagate commands
    while(!m_command_queue.is_empty()) {
        m_graph.on_command(m_command_queue.pop(), dt);
    }

    sf::Vector2f velocity(m_player->get_velocity());
    if(velocity.x != 0 && velocity.y != 0) m_player->set_velocity(velocity / std::sqrt(2.f));
    m_player->accelerate(0.f, m_scroll_speed.y);
    
    m_graph.update(dt);

    // Don't allow player aircraft leave the view
    sf::FloatRect view_bound {
        m_view.getCenter() - m_view.getSize() / 2.f,
        m_view.getSize()
    };
    float border_distance = 110.f;
    sf::Vector2f position = m_player->getPosition();
    
    position.x = std::min(position.x, view_bound.left + view_bound.width - border_distance);
    position.x = std::max(position.x, view_bound.left + border_distance);
    position.y = std::max(position.y, view_bound.top + border_distance / 2.5f);
    position.y = std::min(position.y, view_bound.top + view_bound.height - border_distance);

    m_player->setPosition(position);
}

void World::draw() const {
    m_window.setView(m_view);
    m_window.draw(m_graph);
}

Aircraft& World::get_player() const {
    return *m_player;
}

const sf::View& World::get_view() const { return m_view; }

CommandQueue& World::get_command_queue() {
    return m_command_queue;
}