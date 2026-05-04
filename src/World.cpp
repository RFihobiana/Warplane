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

World::World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
: m_window(window)
, m_textures(textures)
, m_fonts(fonts)

, m_view(window.getDefaultView())
, m_world_bound(
    0.f,
    0.f,
    m_view.getSize().x,
    4000.f
)
, m_scroll_speed(0.f, -80.f)
, m_spawn_player(
    m_world_bound.left + m_world_bound.width / 2,
    m_world_bound.top + m_world_bound.height - m_view.getSize().y / 2
) {
    m_view.setCenter(m_spawn_player);
    load_resources();
    build();
}

void World::load_resources() {
    /* TEXTURES */

    // Aircraft

    if(!m_textures.has(Textures::Eagle)) m_textures.load(Textures::Eagle, "./assets/images/Eagle.png");
    if(!m_textures.has(Textures::Raptor)) m_textures.load(Textures::Raptor, "./assets/images/Raptor.png");
    if(!m_textures.has(Textures::Avenger)) m_textures.load(Textures::Avenger, "./assets/images/Avenger.png");

    // Buns
    if(!m_textures.has(Textures::Bullet)) m_textures.load(Textures::Bullet, "./assets/images/guns/Bullet.png");
    if(!m_textures.has(Textures::Missile)) m_textures.load(Textures::Missile, "./assets/images/guns/Missile.png");

    // Background
    if(!m_textures.has(Textures::Landscape)) m_textures.load(Textures::Landscape, "./assets/images/Desert.png");
}

sf::FloatRect World::get_battlefield_bounds() const {
    const sf::Vector2f& view_center = m_view.getCenter();
    const sf::Vector2f& view_size = m_view.getSize();
    const sf::Vector2f margin(view_size * 0.2f);
    
    auto bound = sf::FloatRect(
        view_center - (view_size / 2.f),
        view_size
    );
    bound.top -= margin.y;
    bound.left -= margin.x;
    return bound;

}

void World::spawn_enemies() {
    const sf::FloatRect battlefield_bounds = get_battlefield_bounds();
    while(
        !m_enemy_spawn_points.empty()
        && m_enemy_spawn_points.back().y > battlefield_bounds.top
    ) {
        SpawnPoint spawn(m_enemy_spawn_points.back());

        Aircraft::Ptr enemy(new Aircraft(spawn.type, m_textures, m_fonts));
        enemy->setRotation(180.f);
        enemy->setPosition(spawn.x, spawn.y);
        m_layers[Air]->attach_child(std::move(enemy));

        m_enemy_spawn_points.pop_back();
    }
}

void World::add_enemy(const Aircraft::Type type, float relx, float rely) {
    m_enemy_spawn_points.push_back(SpawnPoint(
        type,
        m_spawn_player.x + relx,
        m_spawn_player.y - rely
    ));
}

void World::add_enemies() {
    add_enemy(Aircraft::Raptor, 0.f, 500.f);

    add_enemy(Aircraft::Raptor, -80.f, 1200.f);
    add_enemy(Aircraft::Raptor, 80.f, 1200.f);

    add_enemy(Aircraft::Avenger, 200.f, 1800.f);
    add_enemy(Aircraft::Avenger, 0.f, 1800.f);
    add_enemy(Aircraft::Avenger, -200.f, 1800.f);

    add_enemy(Aircraft::Avenger, 300.f, 2500.f);
    add_enemy(Aircraft::Avenger, 100.f, 2500.f);
    add_enemy(Aircraft::Avenger, -100.f, 2500.f);
    add_enemy(Aircraft::Avenger, -300.f, 2500.f);

    add_enemy(Aircraft::Raptor, -80.f, 3100.f);
    add_enemy(Aircraft::Raptor, 80.f, 3100.f);
    add_enemy(Aircraft::Avenger, 200.f, 3200.f);
    add_enemy(Aircraft::Avenger, 0.f, 3200.f);
    add_enemy(Aircraft::Avenger, -200.f, 3200.f);

    std::ranges::sort(m_enemy_spawn_points, [](const auto& a, const auto& b) {
        return a.y - b.y;
    });
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
    std::unique_ptr<Aircraft> aircraft(new Aircraft(Aircraft::Eagle, m_textures, m_fonts));
    aircraft->setPosition(m_spawn_player);
    aircraft->set_velocity(m_scroll_speed);
    m_player = aircraft.get();
    m_layers[Air]->attach_child(std::move(aircraft));
    
    add_enemies();
}

void World::update(sf::Time& dt) {
    m_view.move(m_scroll_speed * dt.asSeconds());
    m_player->set_velocity(0.f, 0.f);

    spawn_enemies();

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